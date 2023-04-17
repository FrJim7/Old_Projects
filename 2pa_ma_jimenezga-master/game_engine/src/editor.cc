/**
* @file editor.cc
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#include "editor.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


#include <stdio.h>
#include <stdlib.h>
#include "../include/sqlite3.h"
#include <string>
#include <vector>
#include "color.h"
#include "label.h"
#include "sprite.h"
#include "shape.h"
#include "shape_points.h"
#include "background.h"
#include "game_object.h"

struct LoadItem
{
  GameObject* items[100];
  int i = 0;
};

Editor::Editor() {
  selected_ = nullptr;
  to_load = false;
  memset(path_, '\0', 255);
  memset(text_, '\0', 255);
}

void Editor::loadHierachy(std::vector<GameObject*> objects, GameObject *ship_, GameObject *enemy_, GameObject *bullet_) {

  char buf[32];

  ImGui::Begin("Hierachy");

  if(ImGui::Button("Save")) {
      saveDB(objects);
    }
     if(ImGui::Button("Load")) {
      loadDB(objects);
    }

  if (ImGui::TreeNode("Objects")) {
    
    static int selected = -1;
    
    if (ImGui::Selectable(ship_->tag(), selected == 0)) {
        selected = 0;
        selected_ = ship_;
        memcpy(path_, selected_->path(), 255);
    }
    if (ImGui::Selectable(bullet_->tag(), selected == 1)) {
        selected = 1;
        selected_ = bullet_;
    }

    if (ImGui::Selectable(enemy_->tag(), selected == 2)) {
        selected = 2;
        selected_ = enemy_;
    }

    for(int i = 0; i < objects.size(); i++) {
      switch(objects[i]->type()) {
        case 0: sprintf(buf, "Shape %d", i);
        break;
        case 1: sprintf(buf, "Sprite %d", i);
        break;
        case 2: sprintf(buf, "Label %d", i);
        break;
        case 3: sprintf(buf, "Background %d", i);
        break;
      }
      if (ImGui::Selectable(buf, selected == i + 3)) {
        selected = i + 3;
        selected_ = objects[i];
        if(selected_->type() != 0) {
          memcpy(path_, selected_->path(), 255);
        }
      }
    }
    ImGui::TreePop();
  }
  ImGui::End();    
}


void Editor::loadEditor() {
  ImGui::Begin("Editor");
  if(selected_ != nullptr){
    
    float px = selected_->position().x;
    float py = selected_->position().y;
    float r = selected_->rotation();
    float sx = selected_->scale().x;
    float sy = selected_->scale().y;
    float vel_x = selected_->vel().x;
    float vel_y = selected_->vel().y;
    float coloro[3] = {((float)selected_->o_color().r / 255.f), ((float)selected_->o_color().g / 255.f), ((float)selected_->o_color().b / 255.f)};
    float colorf[3] = {((float)selected_->f_color().r / 255.f), ((float)selected_->f_color().g / 255.f), ((float)selected_->f_color().b / 255.f)};
    Color color_o;
    Color color_f;
    
    if(selected_->type() == kLabel) {
      Label *temp = (Label*)selected_;
      ImGui::InputText("Font", path_, 255);
      if(ImGui::Button("Update Font")) {
        temp->set_font(path_);
        memcpy(path_, selected_->path(), 255);
        memset(path_, '\0', 255);
      }
      ImGui::InputText("Text", text_, 255);
      temp->set_text(text_);
    } else if (selected_->type() != kShape) {
      ImGui::InputText("SpriteRoute", path_, 255);
      if(ImGui::Button("Update Sprite")) {
        selected_->initFromFile(path_);
        memcpy(path_, selected_->path(), 255);
        memset(path_, '\0', 255);
      }
    }
    
    ImGui::InputFloat("Position X", &px, 0.01f, 1.0f);
    ImGui::InputFloat("Position Y", &py, 0.01f, 1.0f);
    selected_->set_position(px, py);

    ImGui::InputFloat("Rotation", &r, 0.01f, 1.0f);
    selected_->set_rotation(r);

    ImGui::InputFloat("Scale X", &sx, 0.01f, 1.0f);
    ImGui::InputFloat("Scale Y", &sy, 0.01f, 1.0f);
    selected_->set_scale(sx, sy);

    ImGui::InputFloat("Velocity X", &vel_x, 0.01f, 1.0f);
    ImGui::InputFloat("Velocity Y", &vel_y, 0.01f, 1.0f);
    selected_->set_velocity(vel_x, vel_y);

    if (ImGui::ColorEdit3("Outline color", coloro)) {
    color_o.r = static_cast<sf::Uint8>(coloro[0] * 255.f);
    color_o.g = static_cast<sf::Uint8>(coloro[1] * 255.f);
    color_o.b = static_cast<sf::Uint8>(coloro[2] * 255.f);
    color_o.a = 255;
    selected_->set_outline_color(color_o);
  }

  if (ImGui::ColorEdit3("Fill color", colorf)) {
    color_f.r = static_cast<sf::Uint8>(colorf[0] * 255.f);
    color_f.g = static_cast<sf::Uint8>(colorf[1] * 255.f);
    color_f.b = static_cast<sf::Uint8>(colorf[2] * 255.f);
    color_f.a = 255;
    selected_->set_fill_color(color_f);
  }

    if(ImGui::Button("Delete")) {
      selected_->set_enable(false);
      selected_ = nullptr;
    }
  }
  ImGui::End();  
}

GameObject* Editor::editCreate() {
  GameObject *object = nullptr;
  
  ImGui::Begin("Creater");
  if(ImGui::Button("Create Sprite")) {
    object = new Sprite();
    object->set_type(kSprite);
  }
  if(ImGui::Button("Create Label")) {
    object = new Label();
    object->set_type(kLabel);
  }
  if(ImGui::Button("Create Shape")) {
    object = new Shape(kSquarePoints, kSquare);
    object->set_type(kShape);
  }
  if(ImGui::Button("Create Background")) {
    object = new Background();
    object->set_type(kBackground);
  } 

  ImGui::End();
  
  return object;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int callbackLoad(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   GameObject *temp;
   LoadItem  *fill = (LoadItem*) NotUsed;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   /*Color t_color;
   unsigned char temp_char[255];*/
      switch(std::stoi(argv[1], nullptr)) {
        case 0: temp = new Shape();
                temp->set_points(kSquarePoints, kSquare);
                temp->set_type(std::stoi(argv[1], nullptr));
                temp->set_position(std::stof(argv[2], nullptr), std::stof(argv[3],nullptr));
                temp->set_rotation(std::stof(argv[4], nullptr));
                temp->set_velocity(std::stof(argv[5], nullptr), std::stof(argv[6], nullptr));
                temp->set_scale(std::stof(argv[7], nullptr), std::stof(argv[8], nullptr));
                temp->set_outline_color({(unsigned char)std::stoi(argv[9], nullptr), (unsigned char)std::stoi(argv[10], nullptr), (unsigned char)std::stoi(argv[11], nullptr)});
                temp->set_fill_color({(unsigned char)std::stoi(argv[12], nullptr), (unsigned char)std::stoi(argv[13], nullptr), (unsigned char)std::stoi(argv[14], nullptr)});
                fill->items[fill->i] = temp;
          break;
        case 1: temp = new Sprite();
                temp->set_type(std::stoi(argv[1], nullptr));
                temp->initFromFile(argv[15]);
                temp->set_position(std::stof(argv[2], nullptr), std::stof(argv[3],nullptr));
                temp->set_rotation(std::stof(argv[4], nullptr));
                temp->set_velocity(std::stof(argv[5], nullptr), std::stof(argv[6], nullptr));
                temp->set_scale(std::stof(argv[7], nullptr), std::stof(argv[8], nullptr));
                temp->set_outline_color({(unsigned char)std::stoi(argv[9], nullptr), (unsigned char)std::stoi(argv[10], nullptr), (unsigned char)std::stoi(argv[11], nullptr)});
                temp->set_fill_color({(unsigned char)std::stoi(argv[12], nullptr), (unsigned char)std::stoi(argv[13], nullptr), (unsigned char)std::stoi(argv[14], nullptr)});
                fill->items[fill->i] = temp;
          break;
        case 2: temp = new Label("", argv[15], std::stof(argv[2], nullptr), std::stof(argv[3],nullptr));
                temp->set_type(std::stoi(argv[1], nullptr));
                temp->initFromFile(argv[15]);
                temp->set_position(std::stof(argv[2], nullptr), std::stof(argv[3],nullptr));
                temp->set_rotation(std::stof(argv[4], nullptr));
                temp->set_velocity(std::stof(argv[5], nullptr), std::stof(argv[6], nullptr));
                temp->set_scale(std::stof(argv[7], nullptr), std::stof(argv[8], nullptr));
                temp->set_outline_color({(unsigned char)std::stoi(argv[9], nullptr), (unsigned char)std::stoi(argv[10], nullptr), (unsigned char)std::stoi(argv[11], nullptr)});
                temp->set_fill_color({(unsigned char)std::stoi(argv[12], nullptr), (unsigned char)std::stoi(argv[13], nullptr), (unsigned char)std::stoi(argv[14], nullptr)});
                fill->items[fill->i] = temp;
          break;
        case 3: temp = new Background();
                temp->set_type(std::stoi(argv[1], nullptr));
                temp->initFromFile(argv[15]);
                temp->set_position(std::stof(argv[2], nullptr), std::stof(argv[3],nullptr));
                temp->set_rotation(std::stof(argv[4], nullptr));
                temp->set_velocity(std::stof(argv[5], nullptr), std::stof(argv[6], nullptr));
                temp->set_scale(std::stof(argv[7], nullptr), std::stof(argv[8], nullptr));
                temp->set_outline_color({(unsigned char)std::stoi(argv[9], nullptr), (unsigned char)std::stoi(argv[10], nullptr), (unsigned char)std::stoi(argv[11], nullptr)});
                temp->set_fill_color({(unsigned char)std::stoi(argv[12], nullptr), (unsigned char)std::stoi(argv[13], nullptr), (unsigned char)std::stoi(argv[14], nullptr)});
                fill->items[fill->i] = temp;
          break;
          
      };
      fill->i += 1;
   return 0;
}

void Editor::createDB() {
   char *zErrMsg = 0;
   char *sql;
   int rc;
   /* Open database */
  sqlite3_open("data.db", &db);
   
   /* Create SQL statement */
   sql = "CREATE TABLE IF NOT EXISTS GAMEOBJECT("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "TYPE           INT,"\
      "PX             FLOAT," \
      "PY             FLOAT," \
      "ANGLE          FLOAT," \
      "VX             FLOAT," \
      "VY             FLOAT," \
      "SX             FLOAT," \
      "SY             FLOAT," \
      "O_R             INT," \
      "O_G             INT," \
      "O_B             INT," \
      "F_R             INT," \
      "F_G             INT," \
      "F_B             INT," \
      "PATH            CHAR(255));";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
}

void Editor::saveDB(std::vector<GameObject*> objects) {
  char *zErrMsg = 0;
   char *sql;
   int rc;

   char temp[2048];
   memset(temp, '\0', 2048);
   /* Open database */
  sqlite3_open("data.db", &db);

  for(int i = 0; i < objects.size(); i++) {
    int sql = sprintf(temp, "INSERT INTO GAMEOBJECT(ID,TYPE,PX,PY,ANGLE,VX,VY,SX,SY,O_R,O_G,O_B,F_R,F_G,F_B,PATH) VALUES (%d,%d,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d,'%s');",i ,objects[i]->type(), objects[i]->position().x, objects[i]->position().y, objects[i]->rotation(), objects[i]->vel().x, objects[i]->vel().y, objects[i]->scale().x, objects[i]->scale().y, (int)objects[i]->o_color().r, (int)objects[i]->o_color().g, (int)objects[i]->o_color().b, (int)objects[i]->f_color().r, (int)objects[i]->f_color().g, (int)objects[i]->f_color().b, objects[i]->path());

    rc = sqlite3_exec(db, temp, callback, 0, &zErrMsg);
    printf("%s\n", temp);
    memset(temp, '\0', 2048);

    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
  }
  sqlite3_close(db);
}

void Editor::loadDB(std::vector<GameObject*> objects) {
  sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("data.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from GAMEOBJECT";

   LoadItem items_;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callbackLoad, &items_, &zErrMsg);
   
   for(int i = 0; i < items_.i; i++) {
    v.push_back(items_.items[i]);
    items_.items[i] = nullptr;
   }
   items_.i = 0;
   to_load = true;

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}
/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "scene_manager.h"

#include "scene.h"
#include "game_manager.h"

#include "sqlite3.h"


SceneManager& SceneManager::instance() {
  static SceneManager* instance = nullptr;

  if(nullptr == instance) {
    instance = new SceneManager();
  }

  return *instance;
}

SceneManager::SceneManager() {
  current_scene_ = kTittle;
  selected_ = 0;
}

void SceneManager::init() {
  for (int i = 0; i < kScenes; ++i) {
    scenes_pool_[i] = nullptr;
  }
  for (int i = 0; i < kPoolSize; ++i) {
    object_pool_[i] = nullptr;
  }
  //scenes_pool_[kTitle]
}

void SceneManager::imgui() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("New")) {
      if (ImGui::Button("Text")) {
        addObject(kText);
      }
      if (ImGui::Button("Sprite")) {
        addObject(kSprite);
      }
      if (ImGui::Button("Rectangle")) {
        addObject(kRectangle);
      }
      if (ImGui::Button("Background")) {
        addObject(kBackground);
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Delete")) {

      ImGui::InputInt("Object id:", &selected_);
      if (ImGui::Button("Confirm")) {
        if(selected_ >= 0) removeObject(selected_);
        selected_ = 0;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
  char temp[kBufferSize];

  for(int i = 0; i < kPoolSize; i++) {
    if (object_pool_[i] != nullptr) {
      snprintf(temp, kBufferSize, "Game Object: %d", i);
      if (ImGui::Selectable(temp)) {
        GManager::instance().inspectable_ = object_pool_[i];
      }
    }
  }
}

void clearData(LoadData *data) {
  data->id = 0;
  data->order = 0;
  data->type = 0;

  data->px = 0;
  data->py = 0;
  data->angle = 0;
  data->scx = 0;
  data->scy = 0;
  data->sx = 0;
  data->sy = 0;

  data->r = 0;
  data->g = 0;
  data->b = 0;
  data->a = 0;

  data->o_r = 0;
  data->o_g = 0;
  data->o_b = 0;
  data->o_a = 0;

  data->text_id = 0;

  snprintf(data->text, kBufferSize, "");
  snprintf(data->font, kBufferSize, "");

  data->vx = 0;
  data->vy = 0;
}

int SceneManager::sceneCallback(void *data, int argc, char **argv, 
  char **azColName) {

  LoadData *temp = (LoadData*)data;

  temp->id = std::atoi(argv[0]);
  temp->order = std::atoi(argv[1]);
  temp->type = std::atoi(argv[2]);

  temp->px = std::atof(argv[3]);
  temp->py = std::atof(argv[4]);
  temp->angle = std::atof(argv[5]);
  temp->scx = std::atof(argv[6]);
  temp->scy = std::atof(argv[7]);
  temp->sx = std::atof(argv[8]);
  temp->sy = std::atof(argv[9]);

  temp->r = std::atoi(argv[10]);
  temp->g = std::atoi(argv[11]);
  temp->b = std::atoi(argv[12]);
  temp->a = std::atoi(argv[13]);

  temp->o_r = std::atoi(argv[14]);
  temp->o_g = std::atoi(argv[15]);
  temp->o_b = std::atoi(argv[16]);
  temp->o_a = std::atoi(argv[17]);

  temp->text_id = std::atoi(argv[18]);

  snprintf(temp->text, kBufferSize, "%s", argv[19]);
  snprintf(temp->font, kBufferSize, "%s", argv[20]);

  temp->vx = std::atof(argv[21]);
  temp->vy = std::atof(argv[22]);

  return 0;
}

void SceneManager::saveDB(sqlite3 *db) {
  int err_code;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  for (int i = 0; i < kPoolSize; ++i) {
    if (object_pool_[i] != nullptr) {
      snprintf(exec, kBufferSize, "INSERT INTO Objects\n VALUES(%d, %d, %d, %f, %f, %f,%f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s', '%s', %f, %f)", object_pool_[i]->id(), object_pool_[i]->order(), object_pool_[i]->type(), object_pool_[i]->position().x, object_pool_[i]->position().y, object_pool_[i]->rotation(), object_pool_[i]->scale().x, object_pool_[i]->scale().y, object_pool_[i]->size().x, object_pool_[i]->size().y, object_pool_[i]->color().r, object_pool_[i]->color().g, object_pool_[i]->color().b, object_pool_[i]->color().a, object_pool_[i]->o_color().r, object_pool_[i]->o_color().g, object_pool_[i]-> o_color().b, object_pool_[i]->o_color().a, object_pool_[i]->texture_id(), object_pool_[i]->text(), object_pool_[i]->font(), object_pool_[i]->velocity().x, object_pool_[i]->velocity().y);
        err_code = sqlite3_exec(db, exec, NULL, 0, NULL);
    } else {
      snprintf(exec, kBufferSize, "DELETE FROM Objects\n WHERE ID=%d", i);
        err_code = sqlite3_exec(db, exec, NULL, 0, NULL);
    }
  }
}

void SceneManager::loadDB(sqlite3 *db) {
  int err_code;
  char *err_msg;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  LoadData data;
  clearData(&data);
  for (int i = 0; i < kPoolSize; ++i) {
    sprintf(exec, "SELECT * from Objects WHERE ID = %d;", i);
    err_code = sqlite3_exec(db, exec, sceneCallback, &data, &err_msg);
    addObject(data, i);
    clearData(&data);
  }
}


void SceneManager::addObject(int type) {
  int aux_index = 0;
  
  for (int i = 0; i < kPoolSize; ++i) {
    if(object_pool_[i] == nullptr) {
      aux_index = i;
      break;
    }
  }

  switch (type) {
    case kNone:
    break;
    case kText: object_pool_[aux_index] = new Text();
    break;
    case kSprite: object_pool_[aux_index] = new Sprite();
    break;
    case kRectangle: object_pool_[aux_index] = new Rectangle();
    break;
    case kBackground: object_pool_[aux_index] = new Background();
    break;
  }

  object_pool_[aux_index]->set_id(aux_index);
}

void SceneManager::addObject(LoadData& data, int id) {
  switch (data.type) {
    case kNone: return;
    break;
    case kText: object_pool_[id] = new Text();
    break;
    case kSprite: object_pool_[id] = new Sprite();
    break;
    case kRectangle: object_pool_[id] = new Rectangle();
    break;
    case kBackground: object_pool_[id] = new Background();
    break;
  }
  object_pool_[id]->set_id(data.id);
  object_pool_[id]->set_order(data.order);
  

  object_pool_[id]->set_position(data.px, data.py);
  object_pool_[id]->set_rotation(data.angle);
  object_pool_[id]->set_scale(data.scx, data.scy);
  object_pool_[id]->set_size(data.sx, data.sy);

  object_pool_[id]->set_color(sf::Color(data.r, data.g, data.b, data.a));
  object_pool_[id]->set_outlinecolor(sf::Color(data.o_r, data.o_g, data.o_b, data.o_a));

  object_pool_[id]->set_texture_id(data.text_id);
  object_pool_[id]->set_text(data.text);
  object_pool_[id]->set_font(data.font);

  object_pool_[id]->set_velocity(data.vx, data.vy);
}

void SceneManager::removeObject(int id) {
  if (object_pool_[id] != nullptr) {
    delete object_pool_[id];
    object_pool_[id] = nullptr;
  }
}

void SceneManager::drawScene(sf::RenderTexture& render) {
  for(int i = 0; i < kPoolSize; i++) {
    if(object_pool_[i] != nullptr) {
      object_pool_[i]->draw(render);
    }
  }
}

void SceneManager::updateScene(double dT) {
  if(!GManager::instance().start_imgui_) {
    for(int i = 0; i < kPoolSize; i++) {
    if(object_pool_[i] != nullptr) {
      object_pool_[i]->update(dT);
    }
  }
  }
}

void SceneManager::changeScene(SceneName scene) {
  current_scene_ = scene;
}

void SceneManager::release() {
  for (int i = 0; i < kScenes; ++i) {
    if (scenes_pool_[i] != nullptr) {
      delete scenes_pool_[i];
    }
  }
  for (int i = 0; i < kPoolSize; ++i) {
    if (object_pool_[i] != nullptr) delete object_pool_[i];
  }
}
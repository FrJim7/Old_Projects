/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "game_manager.h"

#include "sqlite3.h"

#include "game_defs.h"

GManager::GManager() {
  start_imgui_ = false;
}

GManager::GManager(const GManager &other) {}

GManager& GManager::instance() {
  static GManager* instance = nullptr;

  if(nullptr == instance) {
    instance = new GManager();
  }

  return *instance;
}

char* GManager::parsePath(const char *path) {
  if (NULL == path) {
    return;
  }

  int aux_index = 0;
  int start_index = 0;
  int path_length = strlen(path);

  char *parsed_path = (char*)malloc(kBufferSize * sizeof(char));

  memset(parsed_path, 0, kBufferSize);
  parsed_path[0] = '.';
  parsed_path[1] = '.';

  for(int x = 0; x < path_length; ++x) {
    if(path[x] == kGameRoot[aux_index]) {
      aux_index++;
    } else {
      aux_index = 0;
    }
    if(aux_index == kGameRootSize) {
      start_index = x + 1;
    }
  }

  aux_index = 2;

  for (int x = start_index; x < path_length; ++x) {
    parsed_path[aux_index] = path[x];
    aux_index++;
  }

  return parsed_path;
}

/*void GManager::load() {
  int err_code;
  char *err_msg;

  err_code = sqlite3_open("../data/Jg_DB.db", &db);
  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Open DB successfully\n");
  }

  TextureManager::instance().loadDB(db);
  SceneManager::instance().loadDB(db);

  sqlite3_close(db);
}

void GManager::initImGui(sf::RenderWindow& window) {
    ImGui::SFML::Init(window);
    inspectable_ = nullptr;
    viewport = ImGui::GetMainViewport();
    SceneManager::instance().init();

    //allow docking in the ImGui editor
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //window flags to dockNode
    dock_flg_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar;
    dock_flg_ |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    dock_flg_ |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
}

void GManager::updateImGui(sf::RenderWindow& window, sf::RenderTexture& render,
  sf::Time dT) {
  if (start_imgui_) {
    int err_code;
    char *err_msg;
    ImGui::SFML::Update(window, dT);

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("Editor", &w_open_, dock_flg_);
    dockspace_id_ = ImGui::GetID("MyDockSpace");

    ImGui::DockSpace(dockspace_id_, ImVec2(0.0f, 0.0f));

    if (ImGui::BeginMenuBar()) {
      if (ImGui::Button("Save")) {
        
        err_code = sqlite3_open("../data/Jg_DB.db", &db);
        if (err_code != SQLITE_OK) {
          fprintf(stdout, "SQL error: %s\n", err_msg);
          sqlite3_free(err_msg);
        } else {
          fprintf(stdout, "Open DB successfully\n");
        }

        SceneManager::instance().saveDB(db);
        TextureManager::instance().saveDB(db);

        sqlite3_close(db);

      }
      if (ImGui::Button("Load")) {
        load();
      }
      ImGui::EndMenuBar();
    }


    ImGui::Begin("TextureManager", &w_open_, ImGuiWindowFlags_MenuBar);
    TextureManager::instance().imgui();
    ImGui::End();

    ImGui::Begin("Hierachy",&w_open_, ImGuiWindowFlags_MenuBar);
    SceneManager::instance().imgui();
    ImGui::End();

    ImGui::Begin("Inspector");
    if(inspectable_ != nullptr) inspectable_->imgui();
    ImGui::End();

    ImGui::Begin("Render");
    sf::FloatRect texture_rect = sf::FloatRect(0, 0, render.getSize().x, 
      render.getSize().y);
    sf::Vector2f size = ImGui::GetContentRegionAvail();
    ImGui::Image(render, size, texture_rect);
    ImGui::End();

    ImGui::End();
  }
}

void GManager::renderImGui(sf::RenderWindow& window) {
  if (start_imgui_) {
    ImGui::SFML::Render(window);
  }
}*/
/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */

#include "texture_manager.h"

#include "sqlite3.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include "tinyfiledialogs.h"

#include "game_manager.h"

TextureManager::TextureManager() {
}

TextureManager::TextureManager(const TextureManager& other) {
}

TextureManager::~TextureManager() {
}

TextureManager& TextureManager::instance() {
  static TextureManager* instance_ = nullptr;

  if (instance_ == nullptr) {
    instance_ = new TextureManager();
  }

  return *instance_;
}

int TextureManager::init() {
  for (int i = 0; i < kPoolSize; ++i) {
    texture_pool_[i] = (Texture*)malloc(sizeof(Texture));
    if (NULL == texture_pool_[i]) {
      return 1;
    }

    texture_pool_[i]->id = i;
    texture_pool_[i]->count = 0;
    texture_pool_[i]->enable = true;

    memset(texture_pool_[i]->path, 0, kBufferSize);
  }
  
  default_texture_ = (Texture*)malloc(sizeof(Texture));
  default_texture_->texture.loadFromFile("../data/default.png");

  memset(temp_path_, 0, kBufferSize);
  memset(parsed_path_, 0, kBufferSize);

  return 0;
}

void TextureManager::parsePath(const char *path) {
  if (NULL == path) {
    return;
  }

  int aux_index = 0;
  int start_index = 0;
  int path_length = strlen(path);

  memset(parsed_path_, 0, kBufferSize);
  parsed_path_[0] = '.';
  parsed_path_[1] = '.';

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
    parsed_path_[aux_index] = path[x];
    aux_index++;
  }
}

void TextureManager::imgui() {
  const char *kFilterPatterns[2] = { "*.jpg", "*.png" };
  char const *path = nullptr;
  
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("New")) {
      ImGui::MenuItem("New Texture", NULL, false, false);
      ImGui::InputText("Path", temp_path_, kBufferSize);
      ImGui::SameLine();
      if (ImGui::Button("Open")){
        path = tinyfd_openFileDialog(NULL, NULL, 2, kFilterPatterns, NULL, 0);
        parsePath(path);
        snprintf(temp_path_, kBufferSize, "%s", parsed_path_);
      }
      if (ImGui::Button("Create")) {
        addTexture(temp_path_);
        snprintf(temp_path_, kBufferSize, "");
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
  for (int i = 0; i < kPoolSize; ++i) {

    if (!getInternalTexture(i)->enable) {
      ImGui::Selectable("Texture Id:");
      
      if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
        ImGui::SetDragDropPayload("TEXTURE", &i, sizeof(int));
        ImGui::EndDragDropSource();
      }
      if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::Image(getInternalTexture(i)->texture, kDisplaySize);
        ImGui::EndTooltip();
      }

      ImGui::SameLine();
      ImGui::Text("%d  |", getInternalTexture(i)->id);

      ImGui::SameLine();
      ImGui::Text("Source: %s  |", getInternalTexture(i)->path);

      ImGui::SameLine();
      ImGui::Text("Size: %d x %d", getInternalTexture(i)->texture.getSize().x, 
        getInternalTexture(i)->texture.getSize().y);

      if (getInternalTexture(i)->count < 1) {
        if (ImGui::Button("Delete")) {
          removeTexture(i);
        }
      }
      ImGui::Separator();
    }
  }
}

void TextureManager::saveDB(sqlite3 *db) {
  int err_code;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  for (int i = 0; i < kPoolSize; ++i) {
    if (!getInternalTexture(i)->enable) {
      snprintf(exec, kBufferSize, "INSERT INTO Textures\n VALUES(%d, '%s')", getInternalTexture(i)->id, getInternalTexture(i)->path);
        err_code = sqlite3_exec(db, exec, NULL, 0, NULL);
    } else {
      snprintf(exec, kBufferSize, "DELETE FROM Textures\n WHERE ID=%d", i);
        err_code = sqlite3_exec(db, exec, NULL, 0, NULL);
    }
  }
}

int TextureManager::loadCallback(void *data, int argc, char **argv, 
  char **azColName) {
  Texture *temp_data = (Texture*) data;

  temp_data->id   = std::atoi(argv[0]);
  snprintf(temp_data->path, kBufferSize, "%s", argv[1]);

  return 0;
}


void TextureManager::loadDB(sqlite3 *db) {
  int err_code;
  char *err_msg;
  char exec[kBufferSize];
  memset(exec, 0, kBufferSize);

  Texture data;
  data.id = -1;

  for (int i = 0; i < kPoolSize; i++) {
    sprintf(exec, "SELECT * from Textures WHERE ID = %d", i);
    err_code = sqlite3_exec(db, exec, loadCallback, &data, &err_msg);
    if(data.id != -1) {
      addTexture(data.path, data.id);
      data.id = -1;
      memset(data.path, 0, kBufferSize);
    }
  }
}

int TextureManager::addTexture(const char* path) {
  int aux_index = -1;

  for (int i = 0; i < kPoolSize; ++i) {
    if (texture_pool_[i]->enable) {
      aux_index = i;
      break;
    }
  }

  if (aux_index == -1) {
    return 1;
  }

  if (texture_pool_[aux_index]->texture.loadFromFile(path)) {
    texture_pool_[aux_index]->enable = false;

    snprintf(texture_pool_[aux_index]->path, kBufferSize, "%s", path);
  } else {
    return 1;
  }

  return 0;
}

int TextureManager::addTexture(const char* path, int id) {
  if (texture_pool_[id]->texture.loadFromFile(path)) {
    texture_pool_[id]->enable = false;

    snprintf(texture_pool_[id]->path, kBufferSize, "%s", path);
  } else {
    return 1;
  }

  return 0;
}

void TextureManager::removeTexture(int id) {
  texture_pool_[id]->enable = true;
}


Texture* TextureManager::getTexture(int id) {
  if(id == -1) {
    return default_texture_;
  }
  if (!texture_pool_[id]->enable) {
    texture_pool_[id]->count++;
    return texture_pool_[id];
  }
  return NULL;
}

Texture* TextureManager::getInternalTexture(int id) {
  return texture_pool_[id];
}

void TextureManager::releasePool() {
  for (int i = 0; i < kPoolSize; ++i) {
    free(texture_pool_[i]);
  }
  free(default_texture_);
}
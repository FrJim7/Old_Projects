#include "app_manager.h"

AppManager::AppManager() {
  exit_request_ = false;
  app_end_ = false;

  mouse_x_ = 0;
  mouse_y_ = 0;
}

AppManager& AppManager::instance() {
  static AppManager* instance = nullptr;

  if (instance == nullptr) {
    instance = new AppManager();
  }

  return *instance;
}

void AppManager::update() {
  if (exit_request_) {
	  app_end_ = true;
  }
}
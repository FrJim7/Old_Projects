/**
 * JGGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "jgg_window.h"

#include <cstdio>
#include <cstdlib>
#include "SFML/Graphics.hpp"

#include "SQL/sqlite3.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui-SFML.h"
#include "ImGui/imgui_internal.h"

#include "jgg_manager.h"

JWindow::JWindow() {
  data_.width_  = 0;
  data_.height_ = 0;
  data_.framerate_ = 0;
  data_.gsync_ = false;
  data_.fullscreen_ = false;
  snprintf(data_.title_, kTitleSize, "");
}

JWindow::JWindow(const JWindow &other) {
  data_.width_  = other.data_.width_;
  data_.height_ = other.data_.height_;
  data_.framerate_ = other.data_.framerate_;
  data_.gsync_ = other.data_.gsync_;
  data_.fullscreen_ = other.data_.fullscreen_;
  snprintf(data_.title_, kTitleSize, "%s", other.data_.title_);
}

JWindow::~JWindow() {

}

void JWindow::init() {
  window_.create(sf::VideoMode(data_.width_, data_.height_), data_.title_);
  set_framerate(data_.framerate_);
  enableGSync(data_.gsync_);
  enableFullscreen(data_.fullscreen_);
}

void JWindow::init(int width, int height, const char* title, int framerate,
    bool gsync, bool fullscreen) {
  window_.create(sf::VideoMode(width, height), title);
  set_framerate(framerate);
  enableGSync(gsync);
  enableFullscreen(fullscreen);
  data_.width_  = width;
  data_.height_ = height;
  data_.framerate_ = framerate;
  data_.gsync_ = gsync;
  data_.fullscreen_ = fullscreen;
  snprintf(data_.title_, kTitleSize, "%s", title);
}

void JWindow::imgui() {
  ImGui::Text("Window properties");
  
  if(ImGui::BeginMenuBar()) {
    if(ImGui::MenuItem("Save")) {
      updateWindowData();
    }
    if(ImGui::MenuItem("Load")) {
      loadWindowData();
    }
    if(ImGui::MenuItem("Update")) {
      init();
    } 
    ImGui::EndMenuBar();
  }
  
  ImGui::Separator();
  ImGui::InputText("Title", data_.title_, kTitleSize);
  ImGui::SliderInt("Window Width", &data_.width_, 0, 1920);
  ImGui::SliderInt("Window Height", &data_.height_, 0, 1080);
  int w_size[2] = {data_.width_, data_.height_};
  if(ImGui::InputInt2("Window Size", w_size)) {
    data_.width_ = w_size[0];
    data_.height_ = w_size[1];
  }
  ImGui::SliderInt("Framerate", &data_.framerate_, 0, 240);

  if(ImGui::Checkbox("Fullscreen", &data_.fullscreen_)) {
    enableFullscreen(data_.fullscreen_);
  }

  if(ImGui::Checkbox("GSync", &data_.gsync_)) {
    enableGSync(data_.gsync_);
  }
}

void JWindow::loadWindowData() {
  int err_code;
  char *err_msg;

  sqlite3 *db;

  err_code = sqlite3_open("../data/Jg_DB.db", &db);

  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Open DB successfully\n");
  }

  char temp[kLoadExecSize];
  memset(temp, '\0', kLoadExecSize * sizeof(char));

  sprintf(temp, "SELECT * from WINDOW");

  err_code = sqlite3_exec(db, temp, loadCallback, &data_, &err_msg);

  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Load successfully\n");
  }

  sqlite3_close(db);
}

int JWindow::loadCallback(void *data, int argc, char **argv, char **azColName) {
  WindowData *temp_data = (WindowData*) data;

  snprintf(temp_data->title_, kTitleSize, "%s", argv[0]);

  temp_data->width_     = std::atoi(argv[1]);
  temp_data->height_    = std::atoi(argv[2]);
  temp_data->framerate_ = std::atoi(argv[3]);

  temp_data->gsync_      = std::atoi(argv[4]) ? true : false;
  temp_data->fullscreen_ = std::atoi(argv[5]) ? true : false;
  return 0;
}

void JWindow::updateWindowData() {
  int err_code;
  char *err_msg;

  sqlite3 *db;

  err_code = sqlite3_open("../data/Jg_DB.db", &db);

  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Open DB successfully\n");
  }

  char temp[kUpdateExecSize];
  memset(temp, '\0', kUpdateExecSize * sizeof(char));

  snprintf(temp, kUpdateExecSize, "UPDATE WINDOW\n SET window_title='%s', window_width=%d, window_height=%d, window_framerate=%d, window_gsync=%d, window_fullscreen=%d;", data_.title_, data_.width_, data_.height_, data_.framerate_, data_.gsync_ ? 1 : 0, data_.fullscreen_ ? 1 : 0);

  err_code = sqlite3_exec(db, temp, NULL, 0, &err_msg);

  if (err_code != SQLITE_OK) {
    fprintf(stdout, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
  } else {
    fprintf(stdout, "Update successfully\n");
  }

  sqlite3_close(db);
}

void JWindow::clear(sf::Color clear_color) {
  window_.clear(clear_color);
}

bool JWindow::isOpen() {
  return window_.isOpen();
}

void JWindow::display() {
  window_.display();
}

void JWindow::checkEvent() {
  while (window_.pollEvent(event_)) {
      ImGui::SFML::ProcessEvent(event_);
    if (event_.type == sf::Event::Closed) {
      window_.close();
    }
    /*if (event_.key.code == sf::Keyboard::Tab && JManager::instance().editing_) {
      JManager::instance().editing_ = false;
    } else if (event_.key.code == sf::Keyboard::Tab) {
      JManager::instance().editing_ = true;
    }*/
    if (event_.key.code == sf::Keyboard::Escape &&
        data_.fullscreen_) {
      enableFullscreen(false);
    } else if(event_.key.code == sf::Keyboard::Escape &&
        data_.fullscreen_){
      window_.close();
    }
  }
}

void JWindow::enableGSync(bool active) {
  window_.setVerticalSyncEnabled(active);
  data_.gsync_ = active;
}

void JWindow::enableFullscreen(bool active) {
  if (active) {
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    window_.create(desktop, data_.title_, sf::Style::None);
  } else {
    window_.create(sf::VideoMode(data_.width_, data_.height_), 
      data_.title_);
  }
  data_.fullscreen_ = active;
}

void JWindow::set_size(int width, int height) {
  window_.setSize(sf::Vector2u(width, height));
  data_.width_  = width;
  data_.height_ = height;
}

void JWindow::set_title(const char* title) {
  window_.setTitle(title);
  snprintf(data_.title_, kTitleSize, "%s", title);
}

void JWindow::set_framerate(int framerate) {
  window_.setFramerateLimit(framerate);
  data_.framerate_ = framerate;
}

sf::RenderWindow* JWindow::window() {
  return &window_;
}

sf::Vector2u JWindow::size() {
  return window_.getSize();
}

const char* JWindow::title() {
  return data_.title_;
}

bool JWindow::gsync() {
  return data_.gsync_;
}

int JWindow::framerate() {
  return data_.framerate_;
}

bool JWindow::fullscreen() {
  return data_.fullscreen_;
}
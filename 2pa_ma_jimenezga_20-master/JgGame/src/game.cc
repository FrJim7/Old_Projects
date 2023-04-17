/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "game_defs.h"
#include "game_manager.h"
#include "scene_manager.h"
#include "texture_manager.h"

Game::Game() {
  acum_time_ = 0.0f;
  time_step_ = 1.0f / kWindowFramerate;
  current_time_ = 0.0f;

  delta_clock_.restart();
}

Game::~Game() {}

Game::Game(const Game &other) {}

void Game::init() {
  gmanager_ = &GManager::instance();
  smanager_ = &SceneManager::instance();
  TextureManager::instance().init();

  window_.create(sf::VideoMode(kWindowSizeX, kWindowSizeY), "JgGame");
  r_texture_.create(kWindowSizeX, kWindowSizeY);
  window_.setFramerateLimit(kWindowFramerate);

  gmanager_->initImGui(window_);
 
}

void Game::load() {
   gmanager_->load();
}

void Game::input() {
  while (window_.pollEvent(event_)) {
    
    ImGui::SFML::ProcessEvent(event_);

    if (event_.type == sf::Event::KeyPressed) {
      if (event_.key.code == sf::Keyboard::Tab) {
        gmanager_->start_imgui_ = !gmanager_->start_imgui_;
      }
    }
    if (event_.type == sf::Event::Closed) {
      window_.close();
    }
  }
}

void Game::loop() {
  sf::Clock imClock;
  current_time_ = delta_clock_.getElapsedTime().asSeconds();

  while (window_.isOpen()) {
    
    input();

    acum_time_ = delta_clock_.getElapsedTime().asSeconds() - 
      current_time_;
    while (acum_time_ >= time_step_) {
      current_time_ += time_step_;
      //SCENE MANAGER
      smanager_->updateScene(time_step_);
      acum_time_ = delta_clock_.getElapsedTime().asSeconds() - current_time_;
    }

    gmanager_->updateImGui(window_, r_texture_, imClock.restart());

    draw();
  }
}

void Game::draw() {
  r_texture_.clear(sf::Color::Black);
  smanager_->drawScene(r_texture_);
  r_texture_.display();

  spr_.setTexture(r_texture_.getTexture());
  window_.clear();
  if (!gmanager_->start_imgui_) {
    window_.draw(spr_);
  }
  gmanager_->renderImGui(window_);
  window_.display();
}

void Game::end() {
  smanager_->release();
  TextureManager::instance().releasePool();
}
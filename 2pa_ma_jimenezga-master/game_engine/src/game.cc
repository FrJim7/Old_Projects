/**
 * @file game.cc
 * @author     Francisco Jimenez Garcia jimenezga@esat-alumni.com
 */
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "game.h"
#include "game_window.h"
#include "game_manager.h"

#include <vector>
#include "shape.h"
#include "sprite.h"
#include "background.h"
#include "shape_points.h"

#include "stdio.h"
#include "SFML/Graphics.hpp"

/**
 * @brief      Singleton
 *
 *             Static reference to the Singleton, used to store global data.
 */
GameManager *r = GameManager::reference();

Game::Game(){}

Game::Game(const Game& other) {};

Game::~Game(){}


void Game::init() {
  imgui_ = false;
  pressed_ = false;
  r->current_scene.init();
  window_.init();
}

void Game::input() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !pressed_) {
    imgui_ = !imgui_;
    pressed_ = true;
    ImGui::SFML::Init(*window_.window());
  } else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
    pressed_ = false;
  }
}

void Game::mainLoop() {
  sf::Clock deltaClock;
  while(window_.windowOpen()) {
    window_.windowEvent(imgui_);
    window_.clearWindow();

    input();
    if(imgui_) ImGui::SFML::Update(*window_.window(), deltaClock.restart());

    r->current_scene.update(imgui_);
    r->current_scene.draw(&window_);

    if(imgui_) ImGui::SFML::Render(*window_.window());
    window_.displayWindow();

  }
  if(imgui_)ImGui::SFML::Shutdown();
}

void Game::end() {
  delete r;
}
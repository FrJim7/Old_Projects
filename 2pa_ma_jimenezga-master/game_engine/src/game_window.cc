/**
* @file game_window.cc
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "game_window.h"

#include "SFML/Graphics.hpp"

Window::Window() {
  window_.create(sf::VideoMode(kDefaultSizeX, kDefaultSizeY), kDefaultTitle);
  window_.setFramerateLimit(kDefaultFPS);
}

Window::Window(unsigned int x, unsigned int y, const char* name) {
  if(0 > x || 0 > y) {
    x = kDefaultSizeX;
    y = kDefaultSizeY;
  }
  window_.create(sf::VideoMode(x, y), name);
  window_.setFramerateLimit(kDefaultFPS);
}

Window::~Window() {}

void Window::init() {
  window_.setSize({kDefaultSizeX, kDefaultSizeY});
  window_.setTitle(kDefaultTitle);
}

void Window::init(unsigned int x, unsigned int y, const char* name) {
  if(0 > x || 0 > y) {
    x = kDefaultSizeX;
    y = kDefaultSizeY;
  }
  window_.setSize({x, y});
  window_.setTitle(name);
}

void Window::set_size(unsigned int x, unsigned int y) {
  if(0 > x || 0 > y) return;
  window_.setSize({x, y});
}

void Window::set_title(const char *name) {
  window_.setTitle(name);
}

void Window::clearWindow(sf::Color clear_color) {
  window_.clear(clear_color);
}

void Window::displayWindow() {
  window_.display();
}

bool Window::windowOpen() {
  return window_.isOpen();
}

void Window::windowEvent(bool imgui) {
  sf::Event event;

  while(window_.pollEvent(event)) {
    if(imgui) {
      ImGui::SFML::ProcessEvent(event);
    }
    if (event.type == sf::Event::Closed) window_.close();
  }
}

sf::RenderWindow* Window::window() {
  return &window_;
}
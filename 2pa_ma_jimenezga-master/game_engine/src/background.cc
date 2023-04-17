/**
* @file background.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#include "background.h"
#include "game_window.h"

#include <string>
#include "stdio.h"
#include "SFML/Graphics.hpp"

Background::Background() {
  float widthX = kDefaultSizeX;
  float widthY = kDefaultSizeY;

  set_type(kBackground);
  memset(path_, 0, 255);
  vel_ = {0, 0};
  offset_.top = 0;
  offset_.left = 0;
  offset_.width = kDefaultSizeX;
  offset_.height = kDefaultSizeY;
  back_.setSize({widthX, widthY});
  set_enable(true);
  sprt_ = kNotLoaded;
}

Background::Background(const char *file) {
  float widthX = kDefaultSizeX;
  float widthY = kDefaultSizeY;

  if(handle_.loadFromFile(file)){
    vel_ = {0, 0};
    offset_.top = 0;
    offset_.left = 0;
    offset_.width = kDefaultSizeX;
    offset_.height = kDefaultSizeY;

    handle_.setRepeated(true);

    back_.setSize({widthX, widthY});
    set_enable(true);
    back_.setTextureRect(offset_);
    back_.setTexture(&handle_);
    memset(path_, 0, 255);
    memcpy(path_, file, 255);
    sprt_ = kLoaded;
  } else {
    printf("Error al cargar la textura\n");
    sprt_ = kNotLoaded;
  }
}

Background::Background(const Background &other) {
  offset_ = other.offset_;
  handle_ = other.handle_;
  back_ = other.back_;
  vel_ = other.vel_;
}

Background::~Background() {}

void Background::initFromFile(const char *file) {
  float widthX = kDefaultSizeX;
  float widthY = kDefaultSizeY;

  if(handle_.loadFromFile(file)){
    offset_.width = kDefaultSizeX;
    offset_.height = kDefaultSizeY;
    handle_.setRepeated(true);
    back_.setSize({widthX, widthY});
    set_enable(true);
    back_.setTextureRect(offset_);
    back_.setTexture(&handle_);
    memset(path_, 0, 255);
    memcpy(path_, file, 255);
    sprt_ = kLoaded;
  } else {
    // GUSTAVO: Please try to show error messages in English
    printf("Error al cargar la textura\n");
    sprt_ = kNotLoaded;
  }
}

void Background::set_position(float x, float y) {
  back_.setPosition(x, y);
}

void Background::set_velocity(float x, float y) {
  vel_ = {x, y};
}

void Background::set_size(float width, float height) {
  if(width < 0 || height < 0) return;
  back_.setSize({width, height});
}

void Background::update() {
  offset_.top += vel_.y;
  offset_.left += vel_.x;
  back_.setTextureRect(offset_);
}

void Background::draw(Window *window) {
  window->window()->draw(back_);
}

void Background::move(float x, float y) {
  back_.setPosition(back_.getPosition().x + x, back_.getPosition().y + y);
}

sf::Vector2f Background::position() {
  return back_.getPosition();
}

float Background::rotation() {
  return back_.getRotation();
}

sf::Vector2f Background::scale() {
  return back_.getScale();
}

sf::Vector2u Background::size() {
  return handle_.getSize();
}

sf::Color Background::o_color() {
  return back_.getOutlineColor();
}

sf::Color Background::f_color() {
  return back_.getFillColor();
}

sf::Vector2f Background::vel() {
  return vel_;
}

char* Background::path() {
  return path_;
}

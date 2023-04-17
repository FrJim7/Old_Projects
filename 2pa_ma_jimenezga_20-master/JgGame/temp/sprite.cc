/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */

#include "sprite.h"

Sprite::Sprite() {
  transform_.setPosition(sf::Vector2f(0.0f, 0.0f));
  transform_.setRotation(0.0f);
  transform_.setScale(sf::Vector2f(1.0f, 1.0f));

  transform_.setFillColor(sf::Color::Transparent);
}

Sprite::Sprite(float pos_x, float pos_y, float size_x, float size_y, 
            float scale_x, float scale_y, float rotation, 
            int tid) {
  init(pos_x, pos_y, rotation, size_x, size_y, scale_x, scale_y, 
    outline_color, fill_color);
}

Sprite::~Sprite() {}

void Sprite::init() {
  init(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
    sf::Color::White, sf::Color::Transparent);
}

void Sprite::init(float px, float py, float a, float sx, float sy, 
  float scx, float scy, sf::Color fc, sf::Color oc, int tid, char* file) {
  transform_.setPosition(sf::Vector2f(px, py));
  transform_.setRotation(a);
  transform_.setScale(sf::Vector2f(scx, scy));
  transform_.setTexture(TextureManager::instance().getTexture(tid));
}

void Sprite::set_position(float pos_x, float pos_y) {
  transform_.setPosition(sf::Vector2f(pos_x, pos_y));
}

void Sprite::set_origin(float o_x, float o_y) {
  transform_.setOrigin(o_x, o_y);
}

void Sprite::set_scale(float scale_x, float scale_y) {
  transform_.setScale(scale_x, scale_y);
}

void Sprite::set_size(float size_x, float size_y) {}

void Sprite::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Sprite::set_fillColor(sf::Color fill_color) {
  transform_.setColor(fill_color);
}

void Sprite::set_outlineColor(sf::Color outline_color) {}

void Sprite::set_font(char* file) {}

float Sprite::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Sprite::position() {
  return transform_.getPosition();
}

sf::Vector2f Sprite::origin() {
  return transform_.getOrigin();
}

sf::Vector2f Sprite::scale() {
  return transform_.getScale();
}

sf::Vector2f Sprite::size() {
  return transform_.getSize();
}

sf::Color Sprite::fill_color() {
  return transform_.getColor();
}

sf::Color Sprite::outline_color() {
  return sf::Color::White;
}
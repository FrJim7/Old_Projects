/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "rectangle.h"

Rectangle::Rectangle() {
  transform_.setPosition(sf::Vector2f(0.0f, 0.0f));
  transform_.setRotation(0.0f);
  transform_.setScale(sf::Vector2f(1.0f, 1.0f));
  transform_.setSize(sf::Vector2f(0.0f, 0.0f));

  transform_.setOutlineColor(sf::Color::White);
  transform_.setFillColor(sf::Color::Transparent);
}

Rectangle::Rectangle(float pos_x, float pos_y, float size_x, float size_y, 
            float scale_x, float scale_y, float rotation, 
            sf::Color outline_color, sf::Color fill_color) {
  init(pos_x, pos_y, rotation, size_x, size_y, scale_x, scale_y, 
    outline_color, fill_color);
}

Rectangle::~Rectangle() {}

void Rectangle::init() {
  init(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
    sf::Color::White, sf::Color::Transparent);
}

void Rectangle::init(float px, float py, float a, float sx, float sy, 
  float scx, float scy, sf::Color fc, sf::Color oc, int tid, char* file) {
  transform_.setPosition(sf::Vector2f(px, py));
  transform_.setRotation(a);
  transform_.setScale(sf::Vector2f(scx, scy));
  transform_.setSize(sf::Vector2f(sx, sy));

  transform_.setOutlineColor(oc);
  transform_.setFillColor(fc);
}

void Rectangle::set_position(float pos_x, float pos_y) {
  transform_.setPosition(sf::Vector2f(pos_x, pos_y));
}

void Rectangle::set_origin(float o_x, float o_y) {
  transform_.setOrigin(o_x, o_y);
}

void Rectangle::set_scale(float scale_x, float scale_y) {
  transform_.setScale(scale_x, scale_y);
}

void Rectangle::set_size(float size_x, float size_y) {
  transform_.setSize(sf::Vector2f(size_x, size_y));
}

void Rectangle::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Rectangle::set_fillColor(sf::Color fill_color) {
  transform_.setColor(fill_color);
}

void Rectangle::set_outlineColor(sf::Color outline_color) {
  transform_.setOutlineColor(outline_color);
}

float Rectangle::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Rectangle::position() {
  return transform_.getPosition();
}

sf::Vector2f Rectangle::origin() {
  return transform_.getOrigin();
}

sf::Vector2f Rectangle::scale() {
  return transform_.getScale();
}

sf::Vector2f Rectangle::size() {
  return transform_.getSize();
}

sf::Color Rectangle::fill_color() {
  return transform_.getColor();
}

sf::Color Rectangle::outline_color() {
  return sf::Color::White;
}
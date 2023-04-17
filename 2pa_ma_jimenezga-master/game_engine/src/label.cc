/**
 * @file label.h
 * @author     Francisco Jimenez Garcia jimenezga@esat-alumni.com
 */

#include "label.h"
#include "color.h"
#include <string>
#include "game_window.h"

Label::Label() {
  type_ = kLabel;
  memset(font_path, 0, 255);
  transform_.setString(kDefaultText);
}

Label::Label(const Label &other) {
  font_ = other.font_;
  transform_ = other.transform_;
}

Label::Label(const char* string, const char* file, float px, float py) {
  if(font_.loadFromFile(file)){
    transform_.setFont(font_);
    memcpy(font_path, file, 255);
  } else {
    printf(" Error on font Load\n");
  }
  transform_.setString(string);
  transform_.setPosition({px, py});
}

Label::~Label() {}

void Label::init() {
  transform_.setString(kDefaultText);
  transform_.setPosition(0, 0);
  transform_.setRotation(0);
  transform_.setScale(0, 0);
}

void Label::init(const char* string, const char* file, float px, float py) {
  transform_.setString(string);
  if(font_.loadFromFile(file)){
    transform_.setFont(font_);
    memcpy(font_path, file, 255);
  } else {
    printf(" Error on font Load\n");
  }
  transform_.setPosition(px, py);
  transform_.setRotation(0);
  transform_.setScale(0, 0);
}

void Label::initFromFile(const char *file) { 
  if(font_.loadFromFile(file)){
    transform_.setFont(font_);
    memcpy(font_path, file, 255);
  } else {
    printf(" Error on font Load\n");
  }
}

void Label::set_font(const char* file) {
  if(font_.loadFromFile(file)){
    transform_.setFont(font_);
    memcpy(font_path, file, 255);
  } else {
    printf(" Error on font Load\n");
  }
}

void Label::set_text(const char* string) {
  transform_.setString(string);
}

void Label::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Label::set_rotation(float angle) {
  transform_.setRotation(angle);
}

void Label::set_scale(float scale_x, float scale_y) {
  transform_.setScale(scale_x, scale_x);
}

void Label::set_size(float width, float height) {
  transform_.setCharacterSize(width);
}

void Label::set_outline_color(Color o_color) {
  transform_.setOutlineColor({o_color.r, o_color.g, o_color.b, 255});
}

void Label::set_fill_color(Color f_color) {
  transform_.setFillColor({f_color.r, f_color.g, f_color.b, 255});
}

void Label::draw(Window *window) {
    window->window()->draw(transform_);
}

void Label::move(float x, float y) {
  transform_.setPosition(transform_.getPosition().x + x, transform_.getPosition().y + y);
}

sf::Vector2f Label::position() {
  return transform_.getPosition();
}

float Label::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Label::scale() {
  return transform_.getScale();
}

sf::Color Label::o_color() {
  return transform_.getOutlineColor();
}

sf::Color Label::f_color() {
  return transform_.getFillColor();
}

sf::Vector2u Label::size() {
  sf::Vector2u size(0, 0);
  return size;
}

sf::Vector2f Label::vel() {
  sf::Vector2f vel_(0, 0);
  return vel_;
}

char* Label::path() {
  return font_path;
}
#include "stdio.h"
#include <string>
#include "sprite.h"

unsigned char Sprite::default_texture[16] = {
  0xFF, 0xFF, 0xFF, 0xFF, //white
  0x00, 0x00, 0xFF, 0xFF, //Blue
  0xFF, 0x00, 0x00, 0xFF, //Red
  0xFF, 0xFF, 0xFF, 0xFF  //white
};

Sprite::Sprite() {
  type_ = kSprite;
  memset(path_, 0, 255);
  origin_ = kSpriteOriginUnknown;
}

Sprite::Sprite(const Sprite &other) {
  handle_ = other.handle_;
  origin_ = kSpriteOriginHandle;
  transform_ = other.transform_;
}

Sprite::Sprite(const char *file_name) {
  if(!handle_.loadFromFile(file_name)) {
    handle_.loadFromMemory(default_texture, 16);
    origin_ = kSpriteOriginUnknown;
  } else {
    memcpy(path_, file_name, 255);
    origin_ = kSpriteOriginImage; 
  }
  transform_.setTexture(handle_, true);
}

Sprite::Sprite(const unsigned char *buffer, int size) {
  if(!handle_.loadFromMemory(buffer, size)) {
    handle_.loadFromMemory(default_texture, 16);
    origin_ = kSpriteOriginUnknown;
  } else {
    origin_ = kSpriteOriginBuffer; 
  }
  transform_.setTexture(handle_, true);
}

Sprite::Sprite(sf::Texture handle){
  handle_ = handle;
  origin_ = kSpriteOriginHandle; 
  transform_.setTexture(handle_, true);
}

Sprite::~Sprite() {}

void Sprite::initFromFile(const char *file_name) {
  if(!handle_.loadFromFile(file_name)) {
    handle_.loadFromMemory(default_texture, 16);
    origin_ = kSpriteOriginUnknown;
  } else {
    memcpy(path_, file_name, 255);
    origin_ = kSpriteOriginImage; 
  }
  transform_.setTexture(handle_, true);
}

void Sprite::initFromBuffer(const unsigned char *buffer, int size) {

  if(handle_.loadFromMemory(buffer, size)) {
    handle_.loadFromMemory(default_texture, 16);
    origin_ = kSpriteOriginUnknown;
  } else {
    origin_ = kSpriteOriginBuffer; 
  }
  transform_.setTexture(handle_, true);
}

void Sprite::initFromHandle(sf::Texture handle) {
  if(origin_ != kSpriteOriginUnknown) return;

  handle_ = handle;
  origin_ = kSpriteOriginHandle; 
  transform_.setTexture(handle_, true);
}

void Sprite::set_position(float px, float py) {
  transform_.setPosition({px, py});
}

void Sprite::set_rotation(float angle) {
  transform_.setRotation(angle);
}

void Sprite::set_scale(float scale_x, float scale_y) {
  transform_.setScale({scale_x, scale_y});
}

void Sprite::draw(Window *window) {
  window->window()->draw(transform_);
}

sf::Vector2f Sprite::position() {
  return transform_.getPosition();
}

float Sprite::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Sprite::scale() {
  return transform_.getScale();
}

sf::Vector2u Sprite::size() {
  return handle_.getSize();
}

sf::Vector2f Sprite::vel() {
  sf::Vector2f vel_(0, 0);
  return vel_;
}

sf::Color Sprite::o_color() {
  sf::Color color(0, 0, 0);
  return color;
}

sf::Color Sprite::f_color() {
  sf::Color color(0, 0, 0);
  return color;
}

char* Sprite::path() {
  return path_;
}

void Sprite::move(float x, float y) {
  transform_.setPosition(transform_.getPosition().x + x, transform_.getPosition().y + y);
}

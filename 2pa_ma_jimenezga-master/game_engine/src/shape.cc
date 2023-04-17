/**
* @file shape.cc
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#include "shape.h"
#include "color.h"
#include "stdio.h"
#include "shape_points.h"
#include "SFML/Graphics.hpp"

Shape::Shape() {
  type_ = kShape;
  transform_.setPointCount(kDefaultPoints);
  transform_.setPoint(0, sf::Vector2f({kDefault[0], kDefault[1]}));
  transform_.setPosition(0, 0);
  transform_.setRotation(0);
  transform_.setScale(0, 0);
  transform_.setOutlineColor({kWhite.r, kWhite.g, kWhite.b, kWhite.a});
  transform_.setFillColor({kWhite.r, kWhite.g, kWhite.b, kWhite.a});
  set_enable(true);
}

Shape::Shape(int count, const float *points) {
  int points_position = 0;
  if(0 > count) count = 1;
  transform_.setPointCount(count);
  for(int i = 0; i < count; ++i) {
    transform_.setPoint(i, sf::Vector2f(points[points_position], points[points_position+1]));
    points_position += 2;
  }
  transform_.setPosition(0, 0);
  transform_.setRotation(0);
  transform_.setScale(0, 0);
  transform_.setOutlineColor({kWhite.r, kWhite.g, kWhite.b, 255});
  transform_.setFillColor({kWhite.r, kWhite.g, kWhite.b, 255});
  set_enable(true);
}

Shape::Shape(const Shape &other) {
  transform_ = other.transform_;
}

Shape::~Shape() {}

void Shape::init() {
  transform_.setPointCount(kDefaultPoints);
  transform_.setPoint(0, sf::Vector2f({kDefault[0], kDefault[1]}));
  transform_.setPosition(0, 0);
  transform_.setRotation(0);
  transform_.setScale(0, 0);
  transform_.setOutlineColor({kWhite.r, kWhite.g, kWhite.b, 255});
  transform_.setFillColor({kWhite.r, kWhite.g, kWhite.b, 255});
  set_enable(true);
}

void Shape::init(int count, const float *points) {
  int points_position = 0;
  if(0 > count) count = 1;
  transform_.setPointCount(count);
  for(int i = 0; i < count; ++i) {
    transform_.setPoint(i, sf::Vector2f({points[points_position], points[points_position+1]}));
    points_position += 2;
  }
  transform_.setPosition(0, 0);
  transform_.setRotation(0);
  transform_.setScale(0, 0);
  transform_.setOutlineColor({kWhite.r, kWhite.g, kWhite.b, 255});
  transform_.setFillColor({kWhite.r, kWhite.g, kWhite.b, 255});
  set_enable(true);
}

void Shape::update() {
  transform_.setPosition(position().x + velocity_.x, position().y + velocity_.y);
}

void Shape::set_points(int count, const float *points) {
  int points_position = 0;
  if(0 > count) return;
  if(points == NULL) return;
  transform_.setPointCount(count);
  for(int i = 0; i < count; ++i) {
    transform_.setPoint(i, sf::Vector2f({points[points_position], points[points_position + 1]}));
    points_position += 2;
  }
}

void Shape::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Shape::set_rotation(float angle) {
  transform_.setRotation(angle);
}

void Shape::set_scale(float scale_x, float scale_y) {
  transform_.setScale(scale_x, scale_y);
}

void Shape::set_size(float width, float height) {
  transform_.setScale(width, height);
}

void Shape::set_outline_color(Color o_color) {
  transform_.setOutlineColor({o_color.r, o_color.g, o_color.b, 255});
}

void Shape::set_fill_color(Color f_color) {
  transform_.setFillColor({f_color.r, f_color.g, f_color.b, 255});
}

void Shape::set_velocity(float x, float y) {
  velocity_ = sf::Vector2f(x, y);
}

void Shape::draw(Window *window) {
    window->window()->draw(transform_);
}

void Shape::move(float x, float y) {
  transform_.setPosition(transform_.getPosition().x + x, transform_.getPosition().y + y);
}

sf::Vector2f Shape::position() {
  return transform_.getPosition();
}

float Shape::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Shape::scale() {
  return transform_.getScale();
}

sf::Vector2u Shape::size() {
  sf::Vector2u size(0, 0);
  return size;
}

sf::Color Shape::o_color() {
  return transform_.getOutlineColor();
}

sf::Color Shape::f_color() {
  return transform_.getFillColor();
}
 
sf::Vector2f Shape::vel() {
  sf::Vector2f vel_(0,0);
  return vel_;
}

char* Shape::path() {
  char *a = 0;
  return a;
}
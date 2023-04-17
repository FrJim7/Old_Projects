/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */

#include "game_object.h"

#include <cstdio>

GameObject::GameObject() {
  id_ = 0;
  order_ = 0;
  enable_ = false;
  snprintf(tag_, kTagSize, "Default");
}

GameObject::GameObject(const GameObject &other) {
  id_ = other.id_;
  order_ = other.order_;
  enable_ = other.enable_;
  snprintf(tag_, kTagSize, "%s", other.tag_);
}

GameObject::GameObject(unsigned int id, int order, const char* tag, 
  bool enable) {
  init(id, order, tag, enable);
}

GameObject::~GameObject() {}

void GameObject::init() {
  init(0, 0, "Default", false);
}

void GameObject::init(unsigned int id, int order, const char* tag, 
  bool enable) {
  id_ = id;
  order_ = order;
  enable_ = enable;
  snprintf(tag_, kTagSize, "%s", tag);
}

void GameObject::set_id(unsigned int id) {
  id_ = id;
}

void GameObject::set_tag(const char* tag) {
  snprintf(tag_, kTagSize, "%s", tag);
}

void GameObject::set_enable(bool enable) {
  enable_ = enable;
}

void GameObject::set_order(int order) {
  order_ = order;
}

unsigned int GameObject::id() {
  return id_;
}

int GameObject::order() {
  return order_;
}

bool GameObject::enable() {
  return enable_;
}

const char* GameObject::tag() {
  return tag_;
}
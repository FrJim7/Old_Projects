/**
* @file game_object.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#include <string>
#include "game_object.h"

GameObject::GameObject() {
  id_ = 0;
  enable_ = true;
}

GameObject::GameObject(int id, int type, bool enable) {
  id_ = id;
  type_ = type;
  enable_ = enable;
}

GameObject::GameObject(const GameObject &other) {
  id_ = other.id_;
  enable_ = other.enable_;
}

GameObject::~GameObject() {}

void GameObject::init() {
  init(0, 0);
}

void GameObject::init(int id, int type, bool enable) {
  id_ = id;
  type_ = type;
  enable_ = enable;
}

void GameObject::set_tag(char *tag) {
  memset(tag_, 0, 255);
  memcpy(tag_, tag, 255);
}

void GameObject::set_id(int id) {
  id_ = id;
}

void GameObject::set_type(int type) {
  type_ = type;
}

void GameObject::set_enable(bool enable) {
  enable_ = enable;
}

int GameObject::id() const{
  return id_;
}

char* GameObject::tag(){
  return tag_;
}

int GameObject::type() const {
  return type_;
}

bool GameObject::enable() const{
  return enable_;
}
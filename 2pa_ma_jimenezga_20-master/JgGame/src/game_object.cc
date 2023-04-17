#include "game_object.h"

GameObject::GameObject() {
  id_ = 0;
  type_ = kNone;
  order_ = 0;
  enable_ = true;
}

GameObject::GameObject(const GameObject& other) {
  id_ = other.id_;
  type_ = other.type_;
  order_ = other.order_;
  enable_ = other.enable_;
}

GameObject::~GameObject() {
}

void GameObject::init() {
  id_ = 0;
  type_ = kNone;
  order_ = 0;
  enable_ = true;
}

void GameObject::set_id(int id) {
  id_ = id;
}

void GameObject::set_type(ObjectType type) {
  type_ = type;
}

void GameObject::set_order(int order) {
  order_ = order;
}

void GameObject::set_enable() {
  enable_ = !enable_;
}

int GameObject::id() {
  return id_;
}

ObjectType GameObject::type() {
  return type_;
}

int GameObject::order() {
  return order_;
}

bool GameObject::enable() {
  return enable_;
}
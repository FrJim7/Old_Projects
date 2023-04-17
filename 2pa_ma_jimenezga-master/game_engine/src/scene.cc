/**
* @file scene.cc
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#include "scene.h"
#include "main_scene.h"

#include "game_window.h"

Scene::Scene() {}

Scene::Scene(const Scene& other) {}

Scene::~Scene() {
  delete m_scene_;
}

void Scene::init() {
  m_scene_ = new MainScene();
}

void Scene::update(bool imgui) {
  m_scene_->update(imgui);

}

void Scene::draw(Window *window) {
  m_scene_->draw(window);
}
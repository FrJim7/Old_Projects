/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "scene.h"

#include "game_manager.h"

Scene::Scene() {
  scene_id_ = 0;
}

Scene::Scene(const Scene& other) { 
}

Scene::~Scene() {
}

void Scene::init(int id) {
  scene_id_ = id;
}

/*void Scene::imgui() {
  
}*/

/*void Scene::draw(sf::RenderTexture& render) {
  
}*/

int Scene::scene_id() {
  return scene_id_;
}
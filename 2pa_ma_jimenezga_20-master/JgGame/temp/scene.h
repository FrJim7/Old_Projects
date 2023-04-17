/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include "SFML/Graphics.hpp"

#include "game_defs.h"

class sqlite3;


class Scene {
 public:
  Scene();
  Scene(const Scene& other);
  virtual ~Scene();
   
  //void imgui();

  int scene_id();

  virtual void init(int id);
  virtual void input(){};
  virtual void update(){};
  //void draw(sf::RenderTexture& render);

 private:
  int selected_;
  unsigned int scene_id_;
  
};

#endif//__SCENE_H__
/**
* @file main_scene.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__ 1

#include <vector>
#include "editor.h"
#include "game_object.h"
#include "game_window.h"
#include "game_manager.h"
#include "SFML/Graphics.hpp"

class MainScene {
 public:

  /**
   * @brief      Default Constructor
   */
  MainScene();

  /**
   * @brief      Default Destructor
   */
  ~MainScene();

  /**
   * @brief      Default init
   */
  void init();

  /**
   * @brief      Input
   *
   *             Get the Up and Down key to move the gameobject tagged as Player
   */
  void input();
  
  /**
   * @brief      Update
   *
   *             Controls the game logic, and when imgui is active tells wich
   *             gameobjects must be edited and add gameobjects to the scene
   *
   * @param      current  The current
   * @param[in]  imgui    The imgui
   */
  void update(bool imgui);
  
  /**
   * @brief      Draw
   *
   *             Draw all the game objects in the vector
   *
   * @param      window  The window
   */
  void draw(Window *window);

 

 private:

  float internal_cd;

  float spanw_tick;

  GameObject *ship;

  GameObject *enemy;

  GameObject *bullet;

  Editor editor;

  std::vector<Shape*> enemies;

  std::vector<Shape*> bullets;

  std::vector<GameObject*> main_objects;
  
  MainScene(const MainScene& other);
};

#endif //__MAINSCENE_H__
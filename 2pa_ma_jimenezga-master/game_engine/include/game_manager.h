/**
 * @file game_manager.h
 * @author     Francisco Jimenez Garcia jimenezga@esat-alumni.com
 */
#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__ 1

#include <vector>
#include "scene.h"
#include "sprite.h"
#include "shape.h"
#include "game_object.h"
#include "game_window.h"

/**
 * @brief      GameManager class
 *
 *             This class defines a Singleton that contains all the data needed
 *             and handle the data base.
 */
class GameManager {
 public:
  /**
   * @brief      Reference_ getter
   *
   *             Get a static reference to the Singleton, if it dons't exist it
   *             creates one.
   *
   * @return     Reference to the Singleton
   */
  static GameManager* reference();


  Scene current_scene;

 private:
  /**
   * @brief      Default Constructor
   */
  GameManager();

  /**
   * @brief      Static Singleton reference
   *
   *             Contain the reference to the singleton, it's private so it cant
   *             be called outside the class.
   */
  static GameManager* reference_;
};

#endif //__GAMEMANAGER_H__
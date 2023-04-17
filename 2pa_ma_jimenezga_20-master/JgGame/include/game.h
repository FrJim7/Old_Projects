/**
 * @defgroup   GAME game
 *
 * @brief      This file implements game.
 *
 * @author     Francisco Jimenez Garcia <jimenezga>
 * @date       2019
 */
#ifndef __GAME_H__
#define __GAME_H__ 1

#include "SFML/Graphics.hpp"

/**
 * @brief      This is a forward declaration of GameManager
 */
class GManager;

/**
 * @brief      This is a forward declaration of SceneManager
 */
class SceneManager;

/**
 * @brief      This class describes a game.
 */
class Game {
 public:

  /**
   * @brief      Default constructor
   */
  Game();

 /**
  * @brief      Destroy the object
  */
 ~Game();

  /**
   * @brief      Initializes all the system and the window, must be call before load
   */
  void init();

  /**
   * @brief      Load the game from the database
   */
  void load();
 
  /**
   * @brief      Gets the input and events from the window
   */
  void input();
  
  /**
   * @brief      Main loop
   */
  void loop();

  /**
   * @brief      Draw the game
   */
  void draw();
  
  /**
   * @brief      Release all the reserved data
   */
  void end();

 protected:
  Game(const Game &other);

 private:
  GManager* gmanager_;
  SceneManager* smanager_;

  sf::Event event_;
  sf::Clock delta_clock_;
  
  sf::RenderWindow window_;
  sf::RenderTexture r_texture_;

  sf::Sprite spr_;

  double acum_time_;
  double time_step_;
  double current_time_;
};

#endif//__GAME_H__
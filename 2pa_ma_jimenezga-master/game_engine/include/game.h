/**
* @file game.h 
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __GAME_H__
#define __GAME_H__ 1

#include "game_window.h"
#include "SFML/Graphics.hpp"

const int kWindowX = 1280;
const int kWindowY = 720;

/**
 * @brief      Game class
 *
 *             This class defines the main functions of the program, and
 *             contains all the logic needed to run the game.
 */
class Game {
 public:
  /**
   * @brief      Default Constructor
   */
  Game();
  /**
   * @brief      Default Destructor
   */
  ~Game();

  /**
   * @brief      Init method
   *
   *             The first function call, contains the things than need to be
   *             loaded before the game starts.
   */
  void init();

  void input();
  /**
   * @brief      MainLoop method
   *
   *             This functions is call till the window is closed, contains the
   *             logic of the game and the draw cycle.
   */
  void mainLoop();
  /**
   * @brief      End method
   *
   *             The last function call, release all memory and ends the game.
   */
  void end();

  
 private:
  /**
   * @brief      Copy Constructor
   *
   * @param[in]  other  The other
   */
  Game(const Game& other);

  bool imgui_;

  bool pressed_;

  Window window_;
};

#endif //__GAME_H__
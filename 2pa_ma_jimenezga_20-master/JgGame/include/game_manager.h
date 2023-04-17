/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __GAME_MANAGER_H__ 
#define __GAME_MANAGER_H__ 1

#include "SFML/Graphics.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "game_object.h"

class sqlite3;

class GManager {
 public:
  /**
   * @brief      Returns an instance
   *
   *             Creates an GManager the first time this function is called then
   *             return the created GManager
   *
   * @return     the instance
   */
  static GManager& instance();

  /**
   * @brief      Returns a parsed path to a file
   *
   * @param[in]  path  The path
   *
   * @return     The parsed path
   */
  char* parsePath(const char *path);

  /**
   * @brief      Initializes the imgui graphical user interface.
   *
   * @param      window  The window
   */
  //void initImGui(sf::RenderWindow& window);

  /**
   * @brief      Update the imgui graphical user interface.
   *
   * @param      window  The window
   * @param      render  The render
   * @param[in]  dt      DeltaTime
   */
  //void updateImGui(sf::RenderWindow& window, 
  //  sf::RenderTexture& render, sf::Time dt);

  /**
   * @brief      Renders the imgui graphical user interface.
   *
   * @param      window  The window
   */
  //void renderImGui(sf::RenderWindow& window);

  /**
   * @brief      Load the other systems needed.
   */
  //void load();
  
  /*
  GameObject *inspectable_;*/

 protected:
  /*sqlite3 *db;

  ImGuiID dockspace_id_;
  ImGuiViewport* viewport;

  ImGuiWindowFlags dock_flg_;
  ImGuiWindowFlags render_flg_;

  bool w_open_;*/

 private:

  /**
   * @brief      Constructs a new instance.
   */
  GManager();
  
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  other  The other
   */
  GManager(const GManager &other);
};

#endif//__GAME_MANAGER_H__
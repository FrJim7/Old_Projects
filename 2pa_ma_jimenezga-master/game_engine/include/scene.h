/**
* @file scene.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __SCENE_H__
#define __SCENE_H__ 1

class MainScene;

#include "game_window.h"

/**
 * @brief      Defines a Scene
 *
 *             Defines a abstract class scene. It handle all the things to be
 *             draw in the game
 */
class Scene {
 public:
  /**
   * @brief      Default Constructor
   */
  Scene();
  /**
   * @brief      Default Destructor
   */
  ~Scene();

  /**
   * @brief      Init the scene
   */
  void init();

  /**
   * @brief      Update the scene
   *
   * @param[in]  imgui  Is active
   */
  void update(bool imgui);
  
  /**
   * @brief      Draw the scene
   *
   * @param      window  The window
   */
  void draw(Window *window);

  MainScene *m_scene_;
  

 private:
  /**
  * @brief Copy Constructor
  */
  Scene(const Scene &other);
};

#endif //__SCENE_H__

/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__ 1

#include "SFML/Graphics.hpp"
#include "scene.h"

#include "game_text.h"
#include "game_sprite.h"
#include "game_rectangle.h"
#include "game_background.h"

class sqlite3;

/**
 * @brief      Enum defining the Type of Scene
 */
enum SceneName {
  kTittle = 0,
  kMain = 1,
  kEnd = 2
};

/**
 * @brief      Data to load for the data base
 */
struct LoadData{
  int id;
  int order;
  int type;
  float px;
  float py;
  float angle;
  float scx;
  float scy;
  float sx;
  float sy;
  int r;
  int g;
  int b;
  int a;
  int o_r;
  int o_g;
  int o_b;
  int o_a;
  int text_id;
  char text[kBufferSize];
  char font[kBufferSize];
  float vx;
  float vy;
};

class SceneManager {
 public:
  /**
   * @brief      { function_description }
   *
   * @return     { description_of_the_return_value }
   */
  static SceneManager& instance();

  /**
   * @brief      Returns an instance
   *
   *             Creates an GManager the first time this function is called then
   *             return the created GManager
   *
   * @return     the instance
   */
  void init();
  /**
   * @brief      Display the imgui interface
   */
  void imgui();
  /**
   * @brief      Saves the data in the db.
   *
   * @param      db    The database
   */
  void loadDB(sqlite3 *db);
  /**
   * @brief      Loads the data from the db.
   *
   * @param      db    The database
   */
  void saveDB(sqlite3 *db);
  
  /**
   * @brief      Draw the no nullptr objects in the scene
   *
   * @param      render  The render
   */
  void drawScene(sf::RenderTexture& render);
  /**
   * @brief      Updates the no nullprt objects in the scene.
   *
   * @param[in]  dT    The deltaTime
   *
   */
  void updateScene(double dT);
  /**
   * @brief      Does nothing
   *
   * @param[in]  scene  The scene
   */
  void changeScene(SceneName scene);

  /**
   * @brief      Adds an object.
   *
   * @param[in]  type  The type
   */
  void addObject(int type);
  /**
   * @brief      Adds an object.
   *
   * @param      data  The data
   * @param[in]  id    The identifier
   */
  void addObject(LoadData& data, int id);
  /**
   * @brief      Removes an object.
   *
   * @param[in]  id    The identifier
   */
  void removeObject(int id);

  /**
   * @brief      Load calllback for the gameobjects
   *
   * @param      data       The data
   * @param[in]  argc       The count of arguments
   * @param      argv       The arguments array
   * @param      azColName  The az col name
   *
   * @return     { description_of_the_return_value }
   */
  static int sceneCallback(void *data, int argc, char **argv, 
  char **azColName);

  /**
   * @brief      Release the memory when called
   */
  void release();

  /**
   * @brief      Return the current scene
   *
   * @return     The scene name.
   */
  inline SceneName current_scene() {
    return current_scene_;
  }

 private:
  /**
   * @brief      Constructs a new instance.
   */
  SceneManager();
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  other  The other
   */
  SceneManager(const SceneManager& other) {};
  
  int selected_;
  Scene* scenes_pool_[kScenes];
  GameObject* object_pool_[kPoolSize];
  SceneName current_scene_;
};

#endif//__SCENE_MANAGER_H__
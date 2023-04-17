/**
 * @defgroup   TEXTURE_MANAGER texture manager
 *
 * @brief      This file implements texture manager.
 *
 * @author     Francisco Jimenez Garcia <jimenezga>
 * @date       2019
 */
#ifndef __TEXTURE_MANAGER_H__ 
#define __TEXTURE_MANAGER_H__ 1

#include "SFML/Graphics.hpp"

#include "game_defs.h"

class sqlite3;

/**
 * @brief      Struct used to store Texture data
 */
struct Texture {
  char path[kBufferSize];

  unsigned int id;
  unsigned int count;

  sf::Texture texture;
  
  bool enable;
};

class TextureManager {
 public:
  /**
   * @brief      Returns an instance
   *
   *             Creates an TextureManager the first time this function is
   *             called then return the created TextureManager
   *
   * @return     the instance
   */
  static TextureManager& instance();

  /**
   * @brief      Initializes the object.
   *
   * @return     Error code if not enought memory
   */
  int init();

  /**
   * @brief      Display the imgui interface
   */
  void imgui();

  /**
   * @brief      Saves the data in the db.
   *
   * @param      db    The database
   */
  void saveDB(sqlite3 *db);

  /**
   * @brief      Loads the data from the db.
   *
   * @param      db    The database
   */
  void loadDB(sqlite3 *db);

  /**
   * @brief      Release the memory when called
   */
  void releasePool();

  /**
   * @brief      Gets the texture.
   *
   * @param[in]  id    The identifier
   *
   * @return     The texture.
   */
  Texture* getTexture(int id);

 protected:

  /**
   * @brief      Constructs a new instance.
   */
  TextureManager();
  
  /**
   * @brief      Constructs a new instance.
   *
   * @param[in]  other  The other
   */
  TextureManager(const TextureManager& other);
 
 /**
  * @brief      Destroys the object.
  */
 ~TextureManager();  

  /**
   * @brief      Get the relative route from a path
   *
   *             Get the relative route from a path, the path must contain the
   *             kRoot in order to work
   *
   * @param[in]  path  The path
   */
  void parsePath(const char *path);

  /**
   * @brief      Adds a texture.
   *
   * @param[in]  path  The path
   *
   * @return     Error Codes
   */
  int addTexture(const char* path);

  /**
   * @brief      Adds a texture in a specific slot.
   *
   * @param[in]  path  The path
   * @param[in]  id    The identifier
   *
   * @return     Error codes
   */
  int addTexture(const char* path, int id);

  /**
   * @brief      Callback used to load from the db
   *
   * @param      data       The data
   * @param[in]  argc       The count of arguments
   * @param      argv       The arguments array
   * @param      azColName  The az col name
   *
   * @return     Error codes
   */
  static int loadCallback(void *data, int argc, char **argv, 
  char **azColName);
  
  /**
   * @brief      Removes a texture.
   *
   * @param[in]  id    The identifier
   */
  void removeTexture(int id);

  /**
   * @brief      Gets the internal texture.
   *
   * @param[in]  id    The identifier
   *
   * @return     The internal texture.
   */
  Texture* getInternalTexture(int id);

 private:
  Texture* default_texture_;
  Texture* texture_pool_[kPoolSize];

  char temp_path_[kBufferSize];
  char parsed_path_[kBufferSize];
};

#endif//__TEXTURE_MANAGER_H__
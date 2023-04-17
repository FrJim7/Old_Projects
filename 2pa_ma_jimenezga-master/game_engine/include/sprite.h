/**
* @file game_instance.h
* @author Francisco Jimenez Garcia jimenezga@esat-alumni.com.
*/
#ifndef __SPRITE_H__
#define __SPRITE_H__ 1
  
#include <string>
#include "game_object.h"
#include "game_window.h"
#include "SFML\Graphics.hpp"

/**
 * @enum Origin emun
 *
 * This emun tells the origin of the sprite, so we can debug.
 */
enum SpriteOrigin {
  kSpriteOriginImage,
  kSpriteOriginBuffer,
  kSpriteOriginHandle,
  kSpriteOriginUnknown
};

/**
 * @brief      Sprite Class
 *
 *             The Sprite class handle a drwable texture and all his methods.
 */
class Sprite : public GameObject {
 public:
  /** @brief      Default Constructor */
  Sprite();
  /**
   * @brief      Copy Constructor
   *
   * @param[in]  other  The other
   * @param      Sprite  &other
   */
  Sprite(const Sprite &other);
  /**
   * @brief      Constructor from Image
   *
   * @param[in]  file_name  The file name
   * @param      Char  *file_name
   */
  Sprite(const char *file_name);
  /**
   * @brief      Constructor from Buffer
   *
   * @param[in]  buffer  The buffer
   * @param[in]  size    The size
   * @param      Char  *buffer
   * @param      Int   size
   */
  Sprite(const unsigned char *buffer, int size);
  /**
   * @brief      Constructor from a Texture
   *
   * @param[in]  handle  The handle
   * @param      sf::Texture  handle
   */
  Sprite(sf::Texture handle);

  /**
   * @brief      Default Destructor
   */
  virtual ~Sprite();

  /**
   * @brief      Init From File
   *
   *             Init the sprite Texture from a given file
   *
   * @param[in]  file_name  The file name
   * @param      Char*  file_name
   */
  void initFromFile(const char *file_name) override;
  /**
   * @brief      Init From Buffer
   *
   *             Init the sprite from a bit buffer
   *
   * @param[in]  buffer  The buffer
   * @param[in]  size    The size
   * @param      Char*  buffer
   * @param      Int    size
   */
  void initFromBuffer(const unsigned char *buffer, int size);
  /**
   * @brief      Init From Handle
   *
   *             Init the sprite from a loaded texture
   *
   * @param[in]  handle  The handle
   * @param      sf::Texture  handle
   */
  void initFromHandle(sf::Texture handle);

  void set_points(int count, const float *points) override {};
  /**
   * @brief      Set Position
   *
   *             Set the position of the sprite
   *
   * @param[in]  px    { parameter_description }
   * @param[in]  py    { parameter_description }
   * @param      float  x
   * @param      float  y
   */
  void set_position(float px, float py) override;
  /**
   * @brief      Set Rotation
   *
   *             Set the rotation of the sprite
   *
   * @param[in]  angle  The angle
   * @param      float  angle
   */
  void set_rotation(float angle) override;
   /**
   * @brief      Set Velocity
   *
   * @param[in]  float  vx
   * @param      float  vy
   */
  void set_velocity(float vx, float vy) override {};
  /**
   * @brief      Set Scale
   *
   *             Set the scale of the sprite
   *
   * @param[in]  scale_x  The scale x
   * @param[in]  scale_y  The scale y
   * @param      float  sx
   * @param      float  sy
   */
  void set_scale(float scale_x, float scale_y) override;
  /**
   * @brief      DrawSprite
   *
   *             Draw the sprite in the window
   *
   * @param      window  window to draw
   */
  void draw(Window *window) override;

  void update() override {};
  /**
   * @brief      Set Size
   *
   *             Do nothing because the size is given with the image
   *
   * @param[in]  width   The width
   * @param[in]  height  The height
   */
  void set_size(float width, float height) override{};
  /**
   * @brief      Set Outline Color
   *
   *             Do nothing because the color is given with the image
   *
   * @param[in]  o_color  The o color
   */
  void set_outline_color(Color o_color) override{};
  /**
   * @brief      Set Fill Color
   *
   *             Do nothing because the color is given with the image
   *
   * @param[in]  f_color  The f color
   */
  void set_fill_color(Color f_color) override{};

  void move(float x, float y) override;


  char path_[255];
  /**
   * @brief      Get Position
   *
   *             Return the position of the sprite
   *
   * @return     sf::Vector2 Current position
   */
  sf::Vector2f position() override;
  /**
   * @brief      Get Scale
   *
   *             Return the scale of the sprite
   *
   * @return     sf::Vector2 Current scale
   */
  sf::Vector2f scale() override;
  /**
   * @brief      Get Size
   *
   *             Return the size of the sprite
   *
   * @return     sf::Vector2 Current size
   */
  sf::Vector2u size() override;
  /**
   * @brief      Get Rotation
   *
   *             Return the rotation of the sprite
   *
   * @return     sf::Vector2 Current rotation
   */
  float rotation() override;

  sf::Vector2f vel() override;
  
  char* path() override;

  sf::Color o_color() override;
  
  sf::Color f_color() override;

  /**Default Texture Loaded*/
  static unsigned char default_texture[16];

 protected:
  /**@brief Enum variable
  *
  * Tell the origin of the sprite texture
  */
  SpriteOrigin origin_;

  /**@brief Texture handle*/
  sf::Texture handle_;
  /**@brief Sprite transform*/
  sf::Sprite transform_;
};

#endif
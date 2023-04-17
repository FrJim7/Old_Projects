/**
 * @file background.h
 * @author     Francisco Jimenez Garcia jimenezga@esat-alumni.com
 */
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__ 1

#include <string>
#include "color.h"
#include "game_object.h"
#include "SFML/Graphics.hpp"

/**
 * @brief      TextureStatus
 */
enum SpriteStatus {
  kLoaded = 1,
  kNotLoaded = 0
};

/**
 * @brief      Background Class
 *
 *             This class defines a texture that is repited in the screen and
 *             can move horizontal and vertical
 */
class Background : public GameObject{
 public:
  /**
   * @brief      Default Constructor
   */
  Background();
  /**
   * @brief      From Image Constructor
   *
   * @param[in]  file  The file
   */
  Background(const char *file);
  /**
   * @brief      Copy Constructor
   *
   * @param[in]  other  The other
   */
  Background(const Background &other);
  /**
   * @brief      Default Destructor
   */
  virtual ~Background();

  /**
   * @brief      Init from file
   *
   *             Init the background texture from a file
   *
   * @param[in]  file  The file
   */
  void initFromFile(const char *file) override;

  /**
   * @brief      Parent Function
   *
   * @param[in]  count   The count
   * @param[in]  points  The points
   */
  void set_points(int count, const float *points) override {};

  /**
   * @brief      Set Position
   *
   *             Set the position of the background
   *
   * @param[in]  px    Position X
   * @param[in]  py    Position Y
   */
  void set_position(float px, float py) override;

  /**
   * @brief      Set Velocity
   *
   *             Set the velocity of Background movement. Negative values will
   *             make the background go in the oposite direction
   *
   * @param      x     horizontal velocity
   * @param      y     vertical velocity
   */
  void set_velocity(float x, float y) override;

  /**
   * @brief      Parent Function
   *
   * @param[in]  angle  The angle
   */
  void set_rotation(float angle) override {};

  /**
   * @brief      Parent Function
   *
   * @param[in]  scale_x  The scale x
   * @param[in]  scale_y  The scale y
   */
  void set_scale(float scale_x, float scale_y) override {};

  /**
   * @brief      Set Size
   *
   *             Set the size of the background
   *
   * @param[in]  width   The width
   * @param[in]  height  The height
   */
  void set_size(float width, float height) override;

  /**
   * @brief      Parent Function
   *
   * @param[in]  o_color  The o color
   */
  void set_outline_color(Color o_color) override {};

  /**
   * @brief      Parent Function
   *
   * @param[in]  f_color  The f color
   */
  void set_fill_color(Color f_color) override {};

  /**
   * @brief      Update Background
   *
   *             update the offset of the texture according to the velocity and
   *             controls when the X or Y are bigger than the screen and reset
   *             it
   */
  void update() override;

  /**
   * @brief      Draw
   *
   *             Draw the Background and all his copies in the given window
   *
   * @param      window  The window
   */
  void draw(Window *window) override;

  /**
   * @brief      Move Background
   *
   *             Moves the bacground in x and y units
   *
   * @param[in]  x     X movement
   * @param[in]  y     Y movement
   */
  void move(float x, float y) override;

  /**
   * @brief      Get Position
   *
   *             Gets the position of the background
   *
   * @return     current position
   */
  sf::Vector2f position() override;

  /**
   * @brief      Get Rotation
   *
   *             Gets the rotation of the background
   *
   * @return     current rotation
   */
  float rotation() override;
  
  /**
   * @brief      Get Scale
   *
   *             Gets the scale of the background
   *
   * @return     current scale
   */
  sf::Vector2f scale() override;
  
  /**
   * @brief      Get Size
   *
   *             Gets the size of the background
   *
   * @return     current size
   */
  sf::Vector2u size() override;
  
  /**
   * @brief      Get Velocity
   *
   *             Gets the velocity of the background
   *
   * @return     current velocity
   */
  sf::Vector2f vel() override;
  
  /**
   * @brief      File path
   *
   * @return     the file path
   */
  char* path() override;

  
  sf::Color o_color() override;
  
  sf::Color f_color() override;

  char path_[255];
  /**
   * @brief      SpriteStatus Reference
   *
   *             Tell the status of the Sprite if is loaded or not
   */
  SpriteStatus sprt_;

  /**
   * @brief      Background Velocity
   *
   *             Tell how fast the background will move
   */
  sf::Vector2f vel_;

  /**
   * @brief      Texture offset
   *
   *             Set the offset of the texture to move it
   */
  sf::IntRect offset_;

  /**
   * @brief      Texture
   *
   *             Texture to be draw in the background
   */
  sf::Texture handle_;

  /**
   * @brief      Rectangle window
   *
   *             Rectangle with the window size wich will display the texture
   *             loaded
   */
  sf::RectangleShape back_;
};

#endif //__BACKGROUND_H__

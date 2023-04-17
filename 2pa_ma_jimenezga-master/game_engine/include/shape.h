/**
* @file shape.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __SHAPE_H__
#define __SHAPE_H__ 1

#include "color.h"
#include "game_object.h"
#include "game_window.h"
#include "SFML/Graphics.hpp"

/**
 * @brief      Shape class
 *
 *             Defines a shape, you must give the points of the shape in order
 *             and the number of points
 */
class Shape : public GameObject {
 public:
  /**
   * @brief      Default Constructor
   */
  Shape();
  /**
   * @brief      Param Constructor
   *
   *             Like default contructor, but recieves points and number of
   *             points, if not set them to Null and 0;
   *
   * @param      count   Number of points
   * @param      points  Array with points
   */
  Shape(int count, const float *points);
  /**
   * @brief      Copy Constructor
   *
   * @param[in]  other  The other
   */
  Shape(const Shape &other);
  /**
   * @brief      Default Destructor
   */
  virtual ~Shape();

  /**
   * @brief      Init function
   *
   *             Set the Shape to default values
   */
  void init();
  /**
   * @brief      Init function with params
   *
   *             Like default inti, but recieves points and number of points, if
   *             not set them to Null and 0;
   *
   * @param      count   Number of points
   * @param      points  Array with points
   */
  void init(int count, const float *points);

  void initFromFile(const char *file) override{};

  /**
   * @brief      Set Points
   *
   *             Set the points of the shape, it must be in order. Set them to
   *             Null and 0 if there are no valid parameters
   *
   * @param      count   Number of points
   * @param      points  Array with points
   */
  void set_points(int count, const float *points) override;

  /**
   * @brief      Set Position
   *
   *             Set the position of the shape
   *
   * @param      px    Postion X
   * @param      py    Postion Y
   */
  void set_position(float px, float py) override;

  /**
   * @brief      Set Rotation
   *
   *             Set the rotation of the shape
   *
   * @param      angle  Angle in deegres
   */
  void set_rotation(float angle) override;
  /**
   * @brief      Set Scale
   *
   *             Set the scale of the shape
   *
   * @param      scale_x  Scale X
   * @param      scale_y  Scale Y
   */
  void set_scale(float scale_x, float scale_y) override;

  /**
   * @brief      Sets the velocity.
   *
   * @param[in]  x     X velocity
   * @param[in]  y     Y velocity
   */
  void set_velocity(float x, float y) override;
  /**
   * @brief      Set Size
   *
   *             Work as set scale, don't use it if you have set a scale first
   *             or later
   *
   * @param[in]  width   The width
   * @param[in]  height  The height
   */
  void set_size(float width, float height) override;
  /**
   * @brief      Set Outline color
   *
   *             Set the outline color of the shape
   *
   * @param      o_color  outline color
   */
  void set_outline_color(Color o_color) override;
  /**
   * @brief      Set Fill color
   *
   *             Set the fill color of the shape
   *
   * @param      f_color  fill color
   */
  void set_fill_color(Color f_color) override;

  /**
   * @brief      Parent Function
   */
  void update() override;

  /**
   * @brief      Draw Shape
   *
   *             Draw the shape in the position set if enable
   *
   * @param      window  The window
   */
  void draw(Window *window) override;

  /**
   * @brief      Move
   *
   *             Move the shape
   *
   * @param[in]  x     X movement
   * @param[in]  y     Y movement
   */
  void move(float x, float y) override;

  /**
   * @brief      Get Position
   *
   * @return     current position
   */
  sf::Vector2f position() override;

  /**
   * @brief      Get Rotaion
   *
   * @return     current rotataion
   */
  float rotation() override;
  
  /**
   * @brief      Get Scale
   *
   * @return     current scale
   */
  sf::Vector2f scale() override;
  
  /**
   * @brief      Get Size
   *
   * @return     current size
   */
  sf::Vector2u size() override;
  
  /**
   * @brief      Get vel
   *
   * @return     current vel
   */
  sf::Vector2f vel() override;
  
  sf::Color o_color() override;
  
  sf::Color f_color() override;

  /**
   * @brief      Get file path
   *
   * @return     file path
   */
  char* path() override;

  /**
   * @brief      Transform variable
   */
  sf::ConvexShape transform_;

  sf::Vector2f velocity_;
};

#endif //__SHAPE_H__
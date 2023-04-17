/**
 * @file label.h
 * @author     Francisco Jimenez Garcia jimenezga@esat-alumni.com
 */
#ifndef __LABEL_H__
#define __LABEL_H__ 1

#include "color.h"
#include <string>
#include "game_window.h"
#include "game_object.h"

const char kDefaultText[] = "Default_text";

/**
 * @brief      Class for label.
 *
 *             Defines the font, position, size and color of a text and draw it
 *             in the screen.
 */
class Label : public GameObject {
 public:
  /**
   * @brief      Default Constructor.
   */
  Label();

  /**
   * @brief      Param Constructor.
   *
   *             Set the font with the file given and his position. Don't set
   *             the rotation, scale and color.
   *
   * @param[in]  string  Text
   * @param[in]  file    Font
   * @param[in]  px      Position in X axis
   * @param[in]  py      Position in Y axis
   */
  Label(const char* string, const char* file, float px, float py);

  /**
   * @brief      Copy Constructor.
   *
   * @param[in]  other  Label reference
   */
  Label(const Label &other);

  /**
   * @brief      Destroys the object.
   */
  ~Label();

  /**
   * @brief      Init
   *
   *             Set the text to its default values, this function will mantain
   *             the font loaded.
   */
  void init();

  /**
   * @brief      Init with Param
   *
   *             Set the text with the params given. Don't set the rotation,
   *             scale and color.
   *
   * @param[in]  string  Text
   * @param[in]  file    Font
   * @param[in]  px      Position in X axis
   * @param[in]  py      Position in Y axis
   */
  void init(const char* string, const char* file, float px = 100, float py = 100);

  void initFromFile(const char *file) override;

  /**
   * @brief      Sets the font of Label.
   *
   *             Set the font of the text with the given font.
   *
   * @param[in]  file  Font
   */
  void set_font(const char* file);

  /**
   * @brief      Sets the text of Label.
   *
   *             Set the text of Label with the string given.
   *
   * @param[in]  string  Text
   */
  void set_text(const char* string);

  /**
   * @brief      Parent Function
   *
   * @param[in]  count   The count
   * @param[in]  points  The points
   */
  void set_points(int count, const float *points) override {};

  /**
   * @brief      Sets the position of Label.
   *
   *             Set the position where the text will be draw.
   *
   * @param[in]  px    Position in X axis
   * @param[in]  py    Position in Y axis
   */
  void set_position(float px, float py) override;

  /**
   * @brief      Sets the rotation of Label.
   *
   *             Set the rotation of the text when draw.
   *
   * @param[in]  angle  The angle in degrees
   */
  void set_rotation(float angle) override;

  /**
   * @brief      Parent funtction
   *
   * @param[in]  vx    velocity X
   * @param[in]  vy    velocity Y
   */
  void set_velocity(float vx, float vy) override {};

  /**
   * @brief      Sets the scale of Label.
   *
   *             Set the scale of the text in both axis.
   *
   * @param[in]  scale_x  Scale in X axis
   * @param[in]  scale_y  Scale in Y axis
   */
  void set_scale(float scale_x, float scale_y) override;

  /**
   * @brief      Does nothing.
   *
   *             This function does nothing.
   *
   * @param[in]  width   The width
   * @param[in]  height  The height
   */
  void set_size(float width, float height = 0) override;

  /**
   * @brief      Sets the outline color of Label.
   *
   *             Set the line color of the text.
   *
   * @param[in]  o_color  The outline color
   */
  void set_outline_color(Color o_color) override;

  /**
   * @brief      Sets the fill color of Label.
   *
   *             Set the fill color of the text, if the font supports it.
   *
   * @param[in]  f_color  The fill color
   */
  void set_fill_color(Color f_color) override;

  /**
   * @brief      Update
   */
  void update() override {};

  /**
   * @brief      Draw
   *
   *             Draw the text in the given window.
   *
   * @param      window  The window
   */
  void draw(Window *window) override;

  /**
   * @brief      Move
   *
   *             Move the label in x and y
   *
   * @param[in]  x     X movement
   * @param[in]  y     Y movement
   */
  void move(float x, float y) override;

  /**
   * @brief      Get Position
   *
   *             Get the current position of the label
   *
   * @return     current position
   */
  sf::Vector2f position() override;
  
  /**
   * @brief      Get Rotation
   *
   *             Get the current rotation of the label
   *
   * @return     current rotation
   */
  float rotation() override;
  
  /**
   * @brief      Get Scale
   *
   *             Get the current scale of the label
   *
   * @return     current scale
   */
  sf::Vector2f scale() override;
  
  /**
   * @brief      Get size
   *
   *             Get the current size of the label
   *
   * @return     current size
   */
  sf::Vector2u size() override;
  
  /**
   * @brief      Get Vel
   *
   * @return     current vel
   */
  sf::Vector2f vel() override;
  
  /**
   * @brief      Get path
   *
   *             Get the current file path of the label
   *
   * @return     Fil path
   */
  char* path() override;

  sf::Color o_color() override;
  
  sf::Color f_color() override;

  char font_path[255];
  /**
   * @brief      Sf::Font reference
   *
   *             Stores the font of the text.
   */
  sf::Font font_;
  
  /**
   * @brief      Sf::Text reference
   *
   *             Stores all the information of Label.
   */
  sf::Text transform_;
};

#endif //__LABEL_H__
/**
 * @file game_object.h
 * @author     Francisco Jimenez Garcia jimenezga@esat-alumni.com
 */
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__ 1

#include <string>
#include "color.h"
#include "game_window.h"
#include "SFML/Graphics.hpp"

const int kShape = 0;
const int kSprite = 1;
const int kLabel = 2;
const int kBackground = 3;

/**
 * @brief      Class for game object.
 */
class GameObject {
 public:

  /**
   * @brief      Default Constructor.
   */
  GameObject();

  /**
   * @brief      Param Constructor
   *
   *             Set the id and enables the Object according to the params
   *
   * @param[in]  id      Identifier number
   * @param[in]  type   type where the object belongs.
   * @param[in]  enable  Is the object enable
   */
  GameObject(int id, int type, bool enable);

  /**
   * @brief      Copy Constructor
   *
   * @param[in]  other  The other
   */
  GameObject(const GameObject &other);

  /**
   * @brief      Default Destructor
   */
  virtual ~GameObject();

  /**
   * @brief      Init the GameObject
   *
   *             Set the id to 0, the type to title, and enable to true
   */
  void init();

  /**
   * @brief      Init the GameObjects with params
   *
   *             Set the id and enables the Object according to the params
   *
   * @param[in]  id      Identifier number
   * @param[in]  type   type where the object belongs.
   * @param[in]  enable  Is the object enable
   */
  void init(int id, int type, bool enable = true);

  /**
   * @brief      Sets the points.
   *
   * @param[in]  count   The count
   * @param[in]  points  The points
   */
  virtual void set_points(int count, const float *points) = 0;
  
  /**
   * @brief      Set Position
   *
   * @param[in]  px    Position X
   * @param[in]  py    Position Y
   */
  virtual void set_position(float px, float py) = 0;

  /**
   * @brief      Set Rotation
   *
   * @param[in]  angle  The angle
   */
  virtual void set_rotation(float angle) = 0;

  /**
   * @brief      Sets the velocity.
   *
   * @param[in]  vx    Velocity in X axis
   * @param[in]  vy    Velocity in Y axis
   */
  virtual void set_velocity(float vx, float vy) = 0;

  /**
   * @brief      Set Scale
   *
   * @param[in]  scale_x  The scale x
   * @param[in]  scale_y  The scale y
   */
  virtual void set_scale(float scale_x, float scale_y) = 0;

  /**
   * @brief      Set Size
   *
   * @param[in]  width   The width
   * @param[in]  height  The height
   */
  virtual void set_size(float width, float height = 0) = 0;

  /**
   * @brief      Set OutlineColor
   *
   * @param[in]  o_color  The outline color
   */
  virtual void set_outline_color(Color o_color) = 0;

  /**
   * @brief      Set FillColor
   *
   * @param[in]  f_color  The fill color
   */
  virtual void set_fill_color(Color f_color) = 0;

  virtual void initFromFile(const char *file) = 0;

  /**
   * @brief      Update
   */
  virtual void update() = 0;

  /**
   * @brief      Move
   *
   * @param[in]  x     move X
   * @param[in]  y     move Y
   */
  virtual void move(float x, float y) = 0;

  /**
   * @brief      Draw
   *
   * @param      window  The window
   */
  virtual void draw(Window *window) = 0;

  /**
   * @brief      Set Id
   *
   *             Set the id according to the parameter given
   *
   * @param[in]  id    The identifier
   */
  void set_id(int id);

  void set_tag(char* tag);

  /**
   * @brief      Sets the type.
   *
   * @param[in]  type  The type
   */
  void set_type(int type);

  /**
   * @brief      Set Enable
   *
   *             Set enable according to the parameter given
   *
   * @param[in]  enable  Is enable
   */
  void set_enable(bool enable);

  /**
   * @brief      Get Id
   *
   *             Get the GameObject id;
   *
   * @return     GameObject id_
   */
  int id() const;

  char* tag();

  /**
   * @brief      Get type
   *
   *             Get the GameObject type identifier;
   *
   * @return     GameObject type_
   */
  int type() const;

  /**
   * @brief      Get Enable
   *
   *             Get the GameObject enable;
   *
   * @return     GameObject enable_
   */
  bool enable() const;

  /**
   * @brief      Get Position
   *
   * @return     Current postion
   */
  virtual sf::Vector2f position() = 0;

  /**
   * @brief      Get Rotation
   *
   * @return     Current Rotation
   */
  virtual float rotation() = 0;

  /**
   * @brief      Get Scale
   *
   * @return     Current Scale
   */
  virtual sf::Vector2f scale() = 0;
  
  /**
   * @brief      Get Size
   *
   * @return     Current Size
   */
  virtual sf::Vector2u size() = 0;
  
  /**
   * @brief      Get Vel
   *
   * @return     current vel
   */
  virtual sf::Vector2f vel() = 0;
  
  /**
   * @brief      Get Path
   *
   * @return     Fie path
   */
  virtual char* path() = 0;
 

  virtual sf::Color o_color() = 0;
  
  virtual sf::Color f_color() = 0;

 protected:
  /**
   * @brief      Identification
   *
   *             Number identifying the GameObject
   */
  int id_;

  /**
   * @brief      type Identification
   *
   *             Number identifying the type
   */
  int type_;

  /**
   * @brief      Is enable
   *
   *             Tells if the GameObject is acqive or not
   */
  bool enable_;

  char tag_[255];
};

#endif //__GAMEOBJECT_H__
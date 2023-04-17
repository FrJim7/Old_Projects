#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__ 1

#include "SFML/Graphics.hpp"

class sqlite3;

enum ObjectType
{
  kNone = 0,
  kText = 1,
  kSprite = 2,
  kRectangle = 3,
  kBackground = 4  
};

class GameObject {
 public:
  GameObject();
  GameObject(const GameObject& other);
  virtual ~GameObject();

  virtual void init();

  void set_id(int id);
  void set_type(ObjectType type);
  void set_order(int order);
  void set_enable();

  int id();
  ObjectType type();
  int order();
  bool enable();

  virtual void imgui() = 0;
  virtual void update(float dt) = 0;
  virtual void draw(sf::RenderTexture& texture) = 0;

  virtual void set_position(float px, float py) = 0;
  virtual void set_rotation(float rotation) = 0;
  virtual void set_scale(float scx, float scy) = 0;
  virtual void set_size(float sx, float sy) = 0;

  virtual void set_color(sf::Color color) = 0;
  virtual void set_outlinecolor(sf::Color o_color) = 0;

  virtual void set_text(char *text) = 0;
  virtual void set_font(char *path) = 0;
  virtual void set_texture_id(int texture_id) = 0; 
  virtual void set_velocity(float vx, float vy) = 0;

  virtual float rotation() = 0;
  virtual sf::Vector2f position() = 0;
  virtual sf::Vector2f scale() = 0;
  virtual sf::Vector2f size() = 0;

  virtual sf::Color color() = 0;
  virtual sf::Color o_color() = 0;

  virtual char* text() = 0;
  virtual char* font() = 0;
  virtual int texture_id() = 0;
  virtual sf::Vector2f velocity() = 0;

 protected:
  int id_;
  int order_;
  ObjectType type_;
  bool enable_;
};

#endif//__GAME_OBJECT_H__
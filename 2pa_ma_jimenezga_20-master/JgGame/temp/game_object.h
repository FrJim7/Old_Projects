/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__ 1

const unsigned int kTagSize = 255;

class GameObject {
 public:
  GameObject();
  GameObject(const GameObject &other);
  GameObject(unsigned int id, int order, const char* tag, bool enable);
  virtual ~GameObject();

  void init(unsigned int id, int order, const char* tag, bool enable);

  void set_id(unsigned int id);
  void set_tag(const char* tag);
  void set_order(int order);
  void set_enable(bool enable);
  
  unsigned int id(); 
  int order();
  bool enable();
  const char* tag();

  //------------------------------------------------------------------------//
  
  virtual void init() = 0;
  virtual void init(float px, float py, float a, float sx, float sy, float scx = 1.0f, float scy = 1, sf::Color fc = sf::Color::White, sf::Color oc = sf::Color::White, int tid = -1, char* file = NULL) = 0;

  virtual void set_position(float pos_x, float pos_y) = 0;
  virtual void set_rotation(float rotation) = 0;
  virtual void set_origin(float o_x, float o_y) = 0;
  virtual void set_scale(float scale_x, float scale_y) = 0;
  virtual void set_size(float size_x, float size_y) = 0;

  virtual void set_fillColor(sf::Color fill_color) = 0;
  virtual void set_outlineColor(sf::Color outline_color) = 0;
  virtual void set_texture(int id = -1) = 0;
  virtual void set_font(char* file) = 0;

  virtual float rotation() = 0;
  virtual sf::Vector2f position() = 0;
  virtual sf::Vector2f scale() = 0;
  virtual sf::Vector2f size() = 0;

  virtual sf::Color fill_color() = 0;
  virtual sf::Color outline_color() = 0;
  virtual int texture() = 0;

 protected:
  unsigned int id_;
  int order_;
  char tag_[kTagSize];
  bool enable_;

};

#endif//__JGE_OBJECT_H__
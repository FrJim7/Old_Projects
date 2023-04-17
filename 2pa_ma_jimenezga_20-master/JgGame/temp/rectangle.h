/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __GAME_RECTANGLE_H__
#define __GAME_RECTANGLE_H__ 1

#include "game_object.h"
#include "SFML/Graphics.hpp"

class Rectangle : public GameObject {
 public:
  Rectangle();
  Rectangle(float pos_x, float pos_y, float size_x, float size_y, 
            float scale_x, float scale_y, float rotation, 
            sf::Color outline_color, sf::Color fill_color);
  virtual ~Rectangle();

  void init() override;
  void init(float px, float py, float a, float sx, float sy, float scx = 1.0f, float scy = 1, sf::Color fc = sf::Color::White, sf::Color oc = sf::Color::White, int tid = -1, char* file = NULL) override;

  void set_position(float pos_x, float pos_y) override;
  void set_rotation(float rotation) override;
  void set_origin(float o_x, float o_y) override;
  void set_scale(float scale_x, float scale_y) override;
  void set_size(float size_x, float size_y) override;

  void set_fillColor(sf::Color fill_color) override;
  void set_outlineColor(sf::Color outline_color) override;
  void set_texture(int id = -1) override;
  void set_font(char* file) override;

  float rotation() override;
  sf::Vector2f position() override;
  sf::Vector2f origin() override;
  sf::Vector2f scale() override;
  sf::Vector2f size() override;

  sf::Color fill_color() override;
  sf::Color outline_color() override;
  int texture() override;

 private:
  Rectangle(const Rectangle& other) {};

  sf::RectangleShape transform_;
};

#endif//__GAME_RECTANGLE_H__
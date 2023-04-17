/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __JGE_TEXTURE_H__
#define __JGE_TEXTURE_H__ 1

#include "SFML/Graphics.hpp"

const int kPathSize = 256;

struct TextureData{
  char path_[kPathSize];
  sf::Texture handler_;
};

class FTexture {
 public:
  FTexture();
 ~FTexture();
  FTexture(const FTexture& other);

  bool loadTexture(const char* path);

  char* path();
  sf::Texture handler();

 private:
  TextureData fdata_;
};

#endif//__JGE_TEXTURE_H__
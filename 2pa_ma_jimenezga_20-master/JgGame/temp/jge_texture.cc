/**
 * JgEngine
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "jge_texture.h"

#include <cstdio>

FTexture::FTexture() {
  snprintf(fdata_.path_, kPathSize, "");
}

FTexture::FTexture(const FTexture& other) {
  fdata_.handler_ = other.fdata_.handler_;
  
}

bool FTexture::loadTexture(const char* path) {
  if(fdata_.handler_.loadFromFile(path)) {
    snprintf(fdata_.path_, kPathSize, "%s", path);
    return true;
  }
  return false;
}

char* FTexture::path() {
  return fdata_.path_;
}

sf::Texture FTexture::handler() {
  return fdata_.handler_;
}
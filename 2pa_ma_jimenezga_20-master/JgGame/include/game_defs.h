/**
 * @defgroup   GAME_DEFS game defs
 *
 * @brief      This file implements game defs.
 *
 * @author     Paco
 * @date       2019
 */
#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__ 1

#include "SFML/Graphics.hpp"

const char kGameRoot[] = "JgGame";
const unsigned int kGameRootSize = sizeof(kGameRoot) - 1;

const unsigned int kBufferSize = 256;
const unsigned int kBufferSizeLarge = 512;

const unsigned int kScenes = 12;
const unsigned int kPoolSize = 512;
const unsigned int kPoolSizeLarge = 1024;

const unsigned int kWindowSizeX = 1280;
const unsigned int kWindowSizeY = 720;
const unsigned int kWindowFramerate = 60;

const sf::Vector2f kDisplaySize = sf::Vector2f(200.0f, 200.0f);

const sf::Vector2f kDefaultPosition = sf::Vector2f(200.0f, 200.0f);
const sf::Vector2f kDefaultScale = sf::Vector2f(1.0f, 1.0f);
const sf::Vector2f kDefaultSize = sf::Vector2f(50.0f, 50.0f);
const float kDefaultRotation = 0.0f;

const sf::Color kDefaultColor = sf::Color::White;

const char kDefaultFont[] = "../data/default.ttf";

#endif//__GAME_DEFS_H__
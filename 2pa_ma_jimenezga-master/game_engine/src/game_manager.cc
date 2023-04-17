/**
* @file game_manager.cc 
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#include "game_manager.h"

#include "shape.h"
#include "sprite.h"
#include "game_window.h"
#include "shape_points.h"
/**
* @brief Refernce set
*
* Set the reference to null. Now it can ve inicializated
*/
GameManager* GameManager::reference_ = nullptr;

GameManager::GameManager() {}

GameManager* GameManager::reference() {
  if(reference_ == nullptr) {
    reference_ = new GameManager();
  }
  
  return reference_;
}

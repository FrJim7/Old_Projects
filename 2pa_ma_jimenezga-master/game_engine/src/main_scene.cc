/**
* @file main_scene.cc
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#include "main_scene.h"

#include "stdio.h"
#include "game_manager.h"
#include "background.h"
#include "sprite.h"
#include "shape_points.h"
#include "shape.h"

//GameManager *r = GameManager::reference();

MainScene::MainScene() {
  GameObject *back = new Background("../data/stars.png");
  back->set_velocity(2, 0);
  back->set_tag("Background");
  back->set_type(3);
  main_objects.push_back(back);

  ship = new Sprite("../data/Ship.png");
  ship->set_type(1);
  ship->set_position(50, kDefaultSizeY/2.0f);
  ship->set_tag("Player");

  bullet = new Shape(kSquarePoints, kSquare);
  bullet->set_type(0);
  bullet->set_size(15, 2.5);
  bullet->set_outline_color(kOrange);
  bullet->set_fill_color(kOrange);
  bullet->set_enable(false);
  bullet->set_tag("Bullet");
  enemy = new Shape(kSquarePoints, kSquare);
  enemy->set_type(0);
  enemy->set_size(25, 25);
  enemy->set_outline_color(kRed);
  enemy->set_fill_color(kRed);
  enemy->set_enable(false);
  enemy->set_tag("Enemy");

  editor.createDB();
}

MainScene::MainScene(const MainScene& other) {}

MainScene::~MainScene() {
  // GUSTAVO: This is a HUGE memory leak. clear() does not delete the objects
  // referenced in the std::vector
  main_objects.clear();
}

void MainScene::init() {
  
}

void MainScene::input() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    ship->set_position(ship->position().x, ship->position().y - 5.0f);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    ship->set_position(ship->position().x, ship->position().y + 5.0f);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && internal_cd < 0.0f) {
    Shape *aux = (Shape*)bullet;
    Shape *temp = new Shape(*aux);
    temp->set_position(ship->position().x + ship->size().x, ship->position().y + ship->size().y/2);
    temp->set_velocity(20.0f, 0);
    temp->set_enable(true);
    bullets.push_back(temp);
    internal_cd = 1.0f;
  } else {
    internal_cd -= 0.1f;
  }

  if(ship->position().y < 0) {
    ship->set_position(ship->position().x, 0);
  } 
  if(ship->position().y > kDefaultSizeY - ship->size().y) {
    ship->set_position(ship->position().x, kDefaultSizeY - ship->size().y);
  }
}

void MainScene::update(bool imgui) {

  if(!imgui) {
  input();
  for (int i = 0; i < main_objects.size(); ++i) {
    main_objects[i]->update();
  }

  for (int j = 0; j < enemies.size(); ++j) {
    enemies[j]->update();
    if(enemies[j]->position().x < 0 - 25) {
      enemies[j]->set_enable(false);
    }
    if(enemies[j]->position().x - (15+ship->size().x) <= ship->position().x && enemies[j]->position().x + ship->size().x >= ship->position().x) {

        if(enemies[j]->position().y - (15+ship->size().y) <= ship->position().y && enemies[j]->position().y + (15+ship->size().y) >= ship->position().y) {
          enemies[j]->set_enable(false);
        }
      }

  }

  for (int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(bullets[i]->position().x > kDefaultSizeX) {
      bullets[i]->set_enable(false);
    }
    for (int j = 0; j < enemies.size(); ++j) {
      if(enemies[j]->position().x - 40 <= bullets[i]->position().x && enemies[j]->position().x + 15 >= bullets[i]->position().x) {

        if(enemies[j]->position().y - 30 <= bullets[i]->position().y && enemies[j]->position().y + 30 >= bullets[i]->position().y) {
            bullets[i]->set_enable(false);
            enemies[j]->set_enable(false);
        } 
      }      
    }
  }

  for (int i = 0; i < bullets.size(); ++i) {
    if(!bullets[i]->enable()) {
      // GUSTAVO: BIG memory leak. erase() does not delete the object,
      // it just removes the pointer
      bullets.erase(bullets.begin() + i);
    }
  }

  for (int i = 0; i < enemies.size(); ++i) {
    if(!enemies[i]->enable()) {
      enemies.erase(enemies.begin() + i);
    }
  }


  if(spanw_tick < 0.0f) {
    Shape *aux = (Shape*)enemy;
    Shape *temp = new Shape(*aux);
    temp->set_position(kDefaultSizeX, 25 + rand() % (kDefaultSizeY-25));
    temp->set_velocity(-10.0f, 0);
    temp->set_enable(true);
    enemies.push_back(temp);
    spanw_tick = 2.5f;
  } else {
    spanw_tick -= 0.1f;
  }
  } else {
    editor.loadHierachy(main_objects, ship, enemy, bullet);
    editor.loadEditor();
    GameObject* temp = editor.editCreate();
    if(temp != nullptr) {
      main_objects.push_back(temp);
    }
    if(editor.to_load) {
      main_objects.clear();
      for(int i = 0; i < editor.v.size(); i++){
        editor.v[i]->set_enable(true);
        main_objects.push_back(editor.v[i]);
      }
      editor.to_load = false;
      editor.v.clear();
    }
    for (int i = 0; i < main_objects.size(); ++i) {
      if(!main_objects[i]->enable()){
        main_objects.erase(main_objects.begin() + i);
      }
    }
  }
}

void MainScene::draw(Window *window) {
  for (int i = 0; i < main_objects.size(); ++i) {
    main_objects[i]->draw(window);
  }
  for (int i = 0; i < bullets.size(); ++i) {
    bullets[i]->draw(window);
  }
  for (int i = 0; i < enemies.size(); ++i) {
    enemies[i]->draw(window);
  }
  ship->draw(window);
}

/**
 * JGGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#ifndef __JGG_WINDOW_H__
#define __JGG_WINDOW_H__ 1

#include "SFML/Graphics.hpp"

const unsigned int kTitleSize      = 255;
const unsigned int kLoadExecSize   = 32;
const unsigned int kUpdateExecSize = 2048;

struct WindowData{
  int width_;
  int height_;
  int framerate_;

  bool gsync_;
  bool fullscreen_;
  char title_[kTitleSize];
};

class JWindow {
 public:

  JWindow();

 ~JWindow();

  void init();

  void init(int width, int height, const char* title, int framerate = 0,
    bool gsync = false, bool fullscreen = false);

  
  void imgui();

  void loadWindowData();

  void updateWindowData();

  void clear(sf::Color clear_color = sf::Color::Black);

  bool isOpen();

  void display();

  void checkEvent();

  void enableGSync(bool active);

  void enableFullscreen(bool active);


  void set_size(int width, int height);

  void set_title(const char* title);

  void set_framerate(int framerate);

  sf::RenderWindow* window();

  sf::Vector2u size();

  const char* title();

  bool gsync();

  int framerate();

  bool fullscreen();

 protected:

  JWindow(const JWindow &other);

  int static loadCallback(void *NotUsed, int argc, 
    char **argv, char **azColName);

 private:
  sf::RenderWindow window_;
  sf::Event event_;
  WindowData data_;
};

#endif//__JGG_WINDOW_H__
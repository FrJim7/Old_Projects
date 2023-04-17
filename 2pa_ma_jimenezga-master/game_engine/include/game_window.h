/**
* @file game_window.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/
#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__ 1

#include "SFML/Graphics.hpp"

/**@brief Default Size */
const unsigned int kDefaultSizeX = 1280;
/**@brief Default Size */
const unsigned int kDefaultSizeY = 720;
/**@brief Default Title */
const char kDefaultTitle[] = "MainWindow";
/**@brief Default FrameRate */
const int kDefaultFPS = 60;

/**
* @brief Window Class
*
* This class creates a window, controls the window events and render textures.
*/
class Window {
 public:
  /**
  * @brief Default Constructor
  *
  * Creates a window 1280x720 with Main Window as title
  */
  Window();
  /**
  *@brief Param Constructor
  *
  * Creates a window with the parameters given
  * @param x: width of the screen, it cant be negative
  * @param y: height of the screen, it cant be negative
  * @param name: title of the screen.
  */
  Window(unsigned int x, unsigned int y, const char* name);
  /**
  * @brief Default Destructor
  */
  ~Window();

  /**
  * @brief Default Init
  *
  * Set the window size 1280x720 with Main Window as title
  */
  void init();
  /**
  *@brief Param Init
  *
  * Set the window with the parameters given
  * @param x: width of the screen, it cant be negative
  * @param y: height of the screen, it cant be negative
  * @param name: title of the screen.
  */
  void init(unsigned int x, unsigned int y, const char *name);

  /**
  * @brief Resize the window
  *
  * Set the size of the window with the parameters given
  * @param x: width of the screen, it cant be negative
  * @param y: height of the screen, it cant be negative
  */
  void set_size(unsigned int x, unsigned int y);
  /**
  * @brief Rename the window
  *
  * Set the name of the window with the parameters given
  * @param name: title of the screen
  */
  void set_title(const char *name);
  /**
  * @brief Tell if the window is open
  *
  * Control if the window is open then return true, if not return false
  * @return The current state of the window
  */
  bool windowOpen();
  /**
   * @brief      Tell if an Event occur
   *
   *             Control if the window still open, if not it close the window
   *
   * @param[in]  imgui  The imgui is open
   */
  void windowEvent(bool imgui);
  /**
  * @brief Clear the window
  *
  * Clear the window with the color given
  * @param clear_color: Black default
  */
  void clearWindow(sf::Color clear_color = sf::Color::Black);
  /**
  * @brief Display the window
  * 
  * Draw in the screen everething that has been render till this call
  */
  void displayWindow();
  /**
  * @brief Window_getter
  * 
  * Get the created window
  * @return Window: Current Window
  */
  sf::RenderWindow* window();
 protected:
  /**
  * @brief SFML window
  */
  sf::RenderWindow window_;
};

#endif //__GAMEWINDOW_H__
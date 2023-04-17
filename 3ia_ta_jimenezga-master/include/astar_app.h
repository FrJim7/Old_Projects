/**
 * @defgroup   AStarApp application
 *
 * @brief      This file implements application.
 *
 * @author     jimenezga
 * @date       2019
 */
#ifndef __ASTAR_APP_H__
#define __ASTAR_APP_H__ 1

#include "SFML/Graphics.hpp"

#include "agent.h"
#include "astar.h"
#include "path.h"

#include <vector>

const int kWindowX = 256;
const int kWindowY = 256;
const int kFrate = 60;

class AStarApp {
 public:
	 /**
	  * @brief      Default constructor
	  */
	 AStarApp();

	 /**
	  * @brief      Initialize the agents, window, and path;
	  */
	 void init();

	 /**
	  * @brief      Start the application
	  */
	 void start();

	 /**
	  * @brief      Recive the input
	  */
	 void input();

	 /**
	  * @brief      Update the agents and the app manager
	  *
	  * @param[in]  dt    { time past }
	  */
	 void update(int dt);

	 /**
	  * @brief      Draw the agents
	  */
	 void draw();
	 void end();

private:
	sf::Event event_;
	sf::Clock clock_;
	sf::RenderWindow window_;

	sf::Sprite map_spr_;
	sf::Texture map_text_;

	AStar astar_o_;

	int acum_time_;
	int time_step_;
	int current_time_;
};

#endif//__APPLICATION_H__
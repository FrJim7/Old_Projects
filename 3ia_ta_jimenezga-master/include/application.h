/**
 * @defgroup   APPLICATION application
 *
 * @brief      This file implements application.
 *
 * @author     jimenezga
 * @date       2019
 */
#ifndef __APPLICATION_H__
#define __APPLICATION_H__ 1

#include "SFML/Graphics.hpp"

#include "agent.h"
#include "path.h"

const int kWindowX = 1280;
const int kWindowY = 720;
const int kFrate = 60;

class Application {
 public:
	 /**
	  * @brief      Default constructor
	  */
	 Application();

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

	Path det_path;
	Path ran_path;
	Path tra_path;
	Path pat_path;
	Agent agent_[4];

	sf::Vertex lineX[2];
	sf::Vertex lineY[2];

	int acum_time_;
	int time_step_;
	int current_time_;
};

#endif//__APPLICATION_H__
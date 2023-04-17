/**
 * @defgroup   AGENT agent
 *
 * @brief      This file implements agent.
 *
 * @author     jimenezga
 * @date       2019
 */


#ifndef __AGENT_H__
#define __AGENT_H__ 1


#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "platform_types.h"
#include "SFML/Graphics.hpp"

#include "path.h"

class Agent {
public:
	Agent();
	~Agent();

	/**
	 * @brief      Initialize the agents
	 *
	 * @param[in]  position  The position
	 * @param[in]  mov_type  The mov type
	 * @param      p         The path reference
	 * @param[in]  factor    The speed_factor
	 * @param[in]  color     The color
	 */
	void init(Vector3 position, MovementType mov_type, Path* p, 
		float factor, sf::Color color = sf::Color::White);

	void move(int dt);
	/**
	 * @brief      Updates the agents
	 *
	 * @param[in]  dt    { time step }
	 */
	void update(int dt);

	/**
	 * @brief      Does nothing
	 *
	 * @param[in]  dt    { time step }
	 */
	void updateMind(int dt);

	/**
	 * @brief      Update the agent depending on the mov type they have
	 *
	 * @param[in]  dt    { time step }
	 */
	void updateBody(int dt);
	
	/**
	 * @brief      Draw the agent in the window 
	 *
	 * @param      window  The window
	 */
	void draw(sf::RenderWindow& window);

	/**
	 * @brief      Does nothing
	 */
	void MOV_Stop();

	/**
	 * @brief      Calculate the direction and when the target is reached
	 */
	void MOV_Determ();

	/**
	 * @brief      Calculate the direction and when the target is reached
	 */
	void MOV_Random();
	/**
	 * @brief      Calculate the direction with the mouse position
	 */
	void MOV_Tracker();

	/**
	 * @brief      Calculate the direction and when the target is reached
	 */
	void MOV_Pattern();
	
private:
	sf::RectangleShape body_;
	AppManager *t;
	
	glm::vec2 velocity_;
	glm::vec2 direction_;
	glm::vec2 target_position_;
	glm::vec2 current_position_;

	float factor_;
	bool target_reached_;
	Path *agent_path_;
	MovementType move_type_;
};

#endif//__AGENT_H__

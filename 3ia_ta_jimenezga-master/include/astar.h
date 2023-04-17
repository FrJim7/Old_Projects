/**
 * @defgroup   AStar
 *
 * @brief      This file implements astar.
 *
 * @author     jimenezga
 * @date       2019
 */
#ifndef __ASTAR_H__
#define __ASTAR_H__ 1

#include "SFML/Graphics.hpp"

#include "glm/vec2.hpp"
#include <vector>

const float kScale = 16.0f;
const float kMaximunCost = 1000000.0f;

struct ANode {
	float f;
	float g;
	float h;
	glm::ivec2 position;
	glm::ivec2 parent_position;
};

class AStar {
 public:
	 /**
	  * @brief      Default constructor
	  */
	 AStar();
	 ~AStar();

	 int init(const char* cost_map_filepath, glm::vec2 start_position, glm::vec2 destination);

	 void makePath();
	 void showPath();

	 bool isValid(glm::ivec2& position);
	 bool isDestination(glm::ivec2& position);
	 
	 bool areEqual(ANode& node1, ANode& node2);
	 float calculateH(glm::ivec2& index1);

private:
	sf::Image cost_map_;

	ANode start_;
	ANode destination_;

	std::vector<ANode> map_;
	std::vector<ANode> open_list_;
	std::vector<ANode> closed_list_;

};

#endif//__ASTAR_H__
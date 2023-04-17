#include "astar.h"

#include <cstdlib>

#include "common_def.h"
#include "app_manager.h"

AStar::AStar() {

}

AStar::~AStar() {
	map_.clear();
	open_list_.clear();
	closed_list_.clear();
}

int AStar::init(const char* cost_map_filepath, glm::vec2 start_position, glm::vec2 destination) {

	if (NULL == cost_map_filepath) {
		return kErrorCode_File;
	}

	cost_map_.loadFromFile(cost_map_filepath);
	
	start_.position = glm::ivec2((int)(start_position.x / kScale), (int)(start_position.y / kScale));
	start_.parent_position = glm::ivec2(-1, -1);

	destination_.position = glm::ivec2((int)(destination.x / kScale), (int)(destination.y / kScale));
	start_.parent_position = glm::ivec2(-1, -1);

	if (!isValid(start_.position)) {
		return kErrorCode_NoValidStart;
	}

	if (!isValid(destination_.position)) {
		return kErrorCode_NoValidDest;
	}

	start_.g = 0.0f;
	start_.h = calculateH(start_.position);
	start_.f = start_.h + start_.g;

	destination_.g = 0.0f;
	destination_.h = 0.0f;
	destination_.f = destination_.h + destination_.g;

	open_list_.push_back(start_);

	return kErrorCode_Ok;
}

void AStar::makePath() {
	bool worse_succesor = false;
	int lowest_cost_node = 0;
	float lowest_f = kMaximunCost;

	while (!open_list_.empty()) {
		lowest_cost_node = 0;
		lowest_f = kMaximunCost;

		for (int i = 0; i < open_list_.size(); i++) {

			if (open_list_.at(i).f < lowest_f) {
				lowest_cost_node = i;
				lowest_f = open_list_.at(i).f;
			}
		}

		ANode node_current = open_list_.at(lowest_cost_node);
		open_list_.erase(open_list_.begin() + lowest_cost_node);

		if (isDestination(node_current.position)) {
			return;
		}
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;
				worse_succesor = false;
				if (!isValid(glm::ivec2(node_current.position.x + i, node_current.position.y + j))) continue;
				

				ANode node_succesor;

				node_succesor.position = glm::ivec2(node_current.position.x + i, node_current.position.y + j);
				if (i == 0 || j == 0) node_succesor.g = node_current.g + 10.0f;
				node_succesor.g = node_current.g + 14.0f;

				for (int z = 0; z < open_list_.size(); z++) {
					if (areEqual(node_succesor, open_list_.at(z))) {
						if (node_succesor.g >= open_list_.at(z).g) {
							worse_succesor = true;
							break;
						}
					}
				}

				if (worse_succesor) continue;

				for (int z = 0; z < closed_list_.size(); z++) {
					if (areEqual(node_succesor, closed_list_.at(z))) {
						if (node_succesor.g >= closed_list_.at(z).g) {
							worse_succesor = true;
							break;
						}
						closed_list_.erase(closed_list_.begin() + z);
					}
				}

				if (worse_succesor) continue;

				for (int z = 0; z < open_list_.size(); z++) {
					if (areEqual(node_succesor, open_list_.at(z))) {
						open_list_.erase(open_list_.begin() + z);
					}
				}

				for (int z = 0; z < closed_list_.size(); z++) {
					if (areEqual(node_succesor, closed_list_.at(z))) {
						closed_list_.erase(closed_list_.begin() + z);
					}
				}

				node_succesor.parent_position = node_current.position;
				node_succesor.h = calculateH(node_succesor.position);
				node_succesor.f = node_succesor.g + node_succesor.h;
				open_list_.push_back(node_succesor);
			}
		}
		closed_list_.push_back(node_current);
	}
	
}

void AStar::showPath() {
	for (int i = 0; i < closed_list_.size(); i++) {
		printf("Node %d: Position x = %d, Position y = %d\n", i, closed_list_.at(i).position.x, closed_list_.at(i).position.y);
	}
}

bool AStar::isValid(glm::ivec2& position) {
	if (position.x < 0 || position.x >= cost_map_.getSize().x) return false;
	if (position.y < 0 || position.y >= cost_map_.getSize().y) return false;
	if (cost_map_.getPixel(position.x, position.y) == sf::Color::Black) return false;

	return true;
}


bool AStar::isDestination(glm::ivec2& position) {
	if (position == destination_.position) return true;

	return false;
}

bool AStar::areEqual(ANode& node1, ANode& node2) {

	return node1.position == node2.position;
}


float AStar::calculateH(glm::ivec2 &index1) {
	glm::vec2 node1 = glm::vec2(((float)index1.x) * kScale, ((float)index1.y) * kScale);
	glm::vec2 node2 = glm::vec2(((float)destination_.position.x) * kScale, ((float)destination_.position.y) * kScale);

	return sqrt( (((node2.x - node1.x) * (node2.x - node1.x)) + ((node2.y - node2.y) * (node2.y - node2.y))) );
}
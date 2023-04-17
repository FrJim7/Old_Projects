#include "agent.h"


Agent::Agent() {
	move_type_ = MovementType::kDeterm;
}

Agent::~Agent() {

}

void Agent::init(Vector3 position, MovementType mov_type, Path* p, float factor, sf::Color color) {
	body_.setPosition(position.x, position.y);
	body_.setSize(sf::Vector2f(50.0f, 50.0f));
	body_.setOrigin(25.0f, 25.0f);
	body_.setFillColor(color);

	agent_path_ = p;

	t = &AppManager::instance();

	if (p != NULL) {
		target_position_ = agent_path_->getNextPoint();
	}
	
	factor_ = factor;
	current_position_ = { position.x, position.y };
	move_type_ = mov_type;
	target_reached_ = true;
}

void Agent::move(int dt) {
	float t = (float)(dt * 0.001);

	velocity_ = (((kAgentSpeed * direction_)* factor_) * t);

	current_position_ += glm::vec2(velocity_.x, velocity_.y);

	body_.setPosition(current_position_.x, current_position_.y);
}

void Agent::update(int dt) {
	
	updateMind(dt);

	updateBody(dt);
}

void Agent::updateBody(int dt) {
	switch (move_type_)
	{
	case MovementType::kStop: MOV_Stop();
		break;
	case MovementType::kDeterm: MOV_Determ();
		break;
	case MovementType::kRandom: MOV_Random();
		break;
	case MovementType::kTracker: MOV_Tracker();
		break;
	case MovementType::kPattern: MOV_Pattern();
		break;
	}
	move(dt);
}

void Agent::updateMind(int dt) {
	
}

void Agent::draw(sf::RenderWindow& window) {
	window.draw(body_);
}

void Agent::MOV_Stop() {
	direction_ = { 0.0f, 0.0f };
}

void Agent::MOV_Determ() {
	glm::vec2 distance = target_position_ - current_position_;

	if (glm::length(distance) <= 0.5f) {
		target_position_ = agent_path_->getNextPoint();
		target_reached_ = true;
	}

	if (target_reached_) {
		distance = target_position_ - current_position_;

		direction_ = glm::normalize(distance);
		target_reached_ = false;
	}
}

void Agent::MOV_Random() {
	glm::vec2 distance = target_position_ - current_position_;

	if (glm::length(distance) <= 0.5f) {
		target_position_ = agent_path_->getNextPoint();
		target_reached_ = true;
	}

	if (target_reached_) {
		distance = target_position_ - current_position_;

		direction_ = glm::normalize(distance);
		target_reached_ = false;
	}
}

void Agent::MOV_Tracker() {
	
	target_position_ = { t->mouse_x_, t->mouse_y_ };
	
	glm::vec2 distance = target_position_ - current_position_;

	direction_ = glm::normalize(distance);

}

void Agent::MOV_Pattern() {
	glm::vec2 distance = target_position_ - current_position_;


	if (glm::length(distance) <= 1.0f) {
		target_position_ = agent_path_->getNextPoint();
		target_reached_ = true;
	}

	if (target_reached_) {
		distance = target_position_ - current_position_;

		direction_ = glm::normalize(distance);
		target_reached_ = false;
	}
}
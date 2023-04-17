#include "astar_app.h"
#include "app_manager.h"
#include <cstdlib>


AStarApp::AStarApp() {
	acum_time_ = 0;
	time_step_ = (int)((1.0f / kFrate) * 1000.0f);
	current_time_ = 0;

	clock_.restart();
}

void AStarApp::init() {
	
	map_text_.loadFromFile("../../../data/gfx/maps/map_03_960x704_layout ABGS.png");

	map_spr_.setTexture(map_text_);
	map_spr_.setPosition(0.0f, 0.0f);

	window_.create(sf::VideoMode(map_text_.getSize().x, map_text_.getSize().y), "AStarApp");
	window_.setFramerateLimit(kFrate);

	astar_o_.init("../../../data/gfx/maps/map_03_60x44_cost.png", { 464, 688 }, { 656, 496 });

	astar_o_.makePath();

	astar_o_.showPath();
}

void AStarApp::input() {
	while (window_.pollEvent(event_)) {

		if (event_.type == sf::Event::Closed) {
			AppManager::instance().exit_request_ = true;
		}

		AppManager::instance().mouse_x_ = ((float)sf::Mouse::getPosition(window_).x);
		AppManager::instance().mouse_y_ = ((float)sf::Mouse::getPosition(window_).y);
	}
}

void AStarApp::start() {
	current_time_ = clock_.getElapsedTime().asMilliseconds();

	while (!AppManager::instance().app_end_) {
		input();

		acum_time_ = clock_.getElapsedTime().asMilliseconds() -
			current_time_;

		while (acum_time_ >= time_step_) {

			current_time_ += time_step_;
			
			update(time_step_);
			
			acum_time_ = clock_.getElapsedTime().asMilliseconds() - 
				current_time_;
		
		}

		draw();
	}
}

void AStarApp::end() {

}

void AStarApp::update(int dt) {

	AppManager::instance().update();
}

void AStarApp::draw() {
	window_.clear();
	
	window_.draw(map_spr_);

	window_.display();
}
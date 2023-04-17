#include "application.h"
#include "app_manager.h"

Application::Application() {
	acum_time_ = 0;
	time_step_ = (int)((1.0f / kFrate) * 1000.0f);
	current_time_ = 0;

	clock_.restart();
}

void Application::init() {
	window_.create(sf::VideoMode(kWindowX, kWindowY), "Application");
	window_.setFramerateLimit(kFrate);

	srand(time(NULL));

	lineX[0] = sf::Vertex(sf::Vector2f(kWindowX * 0.5, 0));
	lineX[1] = sf::Vertex(sf::Vector2f(kWindowX * 0.5, kWindowY));

	lineY[0] = sf::Vertex(sf::Vector2f(0, kWindowY * 0.5));
	lineY[1] = sf::Vertex(sf::Vector2f(kWindowX, kWindowY * 0.5));

	glm::vec2 det_points[] = {
		{(kWindowX * 0.5) - 50.0f, 50.0f},
		{(kWindowX * 0.5) - 50.0f, 270.0f},
		{270.0f, 310.0f},
		{270.0f, 50.0f},
		{50.0f, 50.0f}
	};

	det_path.init(kDeterm, kInfiniteLoop, { 50.0f, 50.0f });
	for (int i = 0; i < 5; ++i) {
		det_path.addPoint(det_points[i]);
	}

	agent_[0].init({ 50.0f, 50.0f }, kDeterm, &det_path, 0.75);

	ran_path.init(kRandom, kInfiniteLoop, { (kWindowX * 0.5) + 50.0f, 50.0f });
	ran_path.calculateRandomPoints({ kWindowX * 0.5, 0 },
		{ kWindowX * 0.5, kWindowY * 0.5 }, 50);

	agent_[1].init({ (kWindowX * 0.5) + 50.0f, 50.0f }, kRandom, &ran_path, 1.0);

	agent_[2].init({ 50.0f, (kWindowY * 0.5) + 50.0f }, kTracker, NULL, 1.25);

	pat_path.init(kPattern, kInfiniteLoop, { (kWindowX * 0.5) + 50.0f, (kWindowY * 0.5) + 50.0f });
	pat_path.addPoint(kDown, 100.0f);
	pat_path.addPoint(kRight, 300.0f);
	pat_path.addPoint(kUp, 50.0f);
	pat_path.addPoint(kLeft, 30.0f);
	pat_path.addPoint(kDown, 200.0f);

	agent_[3].init({ (kWindowX * 0.5) + 50.0f, (kWindowY * 0.5) + 50.0f }, 
		kPattern, &pat_path, 1.5);
}

void Application::input() {
	while (window_.pollEvent(event_)) {

		if (event_.key.code == sf::Keyboard::Escape) {
			AppManager::instance().exit_request_ = true;
		}
		if (event_.type == sf::Event::Closed) {
			AppManager::instance().exit_request_ = true;
		}

		AppManager::instance().mouse_x_ = sf::Mouse::getPosition(window_).x;
		AppManager::instance().mouse_y_ = sf::Mouse::getPosition(window_).y;
	}
}

void Application::start() {
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

void Application::end() {

}

void Application::update(int dt) {
	agent_[0].update(dt);
	agent_[1].update(dt);
	agent_[2].update(dt);
	agent_[3].update(dt);
	AppManager::instance().update();
}

void Application::draw() {
	window_.clear();
	
	window_.draw(lineX, 2, sf::Lines);
	window_.draw(lineY, 2, sf::Lines);

	agent_[0].draw(window_);
	agent_[1].draw(window_);
	agent_[2].draw(window_);
	agent_[3].draw(window_);

	window_.display();
}
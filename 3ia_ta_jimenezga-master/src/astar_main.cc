#include "astar_app.h"

int main(int argc, char **argv) {
	AStarApp app;
	
	app.init();
	app.start();
	app.end();

	return 0;
}
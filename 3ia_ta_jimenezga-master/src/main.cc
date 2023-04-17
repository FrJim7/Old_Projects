#include "application.h"

int main(int argc, char **argv) {
	Application app;
	
	app.init();
	app.start();
	app.end();

	return 0;
}
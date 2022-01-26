#include "sorting.h"
#include <iostream>
using namespace sf;

int main() { 

	App *g = new App(800, 800, 20, 100, "ghotic.ttf"); 

	try {
		g->init();
	}
	catch (...) {
		std::cerr << "Initialization failed!";
		return 0;
	}
	g->run();

	return 0;
}
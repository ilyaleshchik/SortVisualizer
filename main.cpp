#include "sorting.h"
#include <iostream>
using namespace sf;

int main() { 

	App *g;
	try {
		g = new App(800, 800, 20, 100);
	} 
	catch (...) {
		std::cerr << "Build failed!!!";
		exit(0);
	}

	g->init();
	g->run();

	return 0;
}
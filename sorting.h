#include <SFML/Graphics.hpp>
#include "myobj.h"
#include <string>
using namespace sf;
#pragma once

class App {

private:
	int nScreenWidth, nScreenHeight;
	int nFieldSize;
	int nVisualSpeed = 0;
	int lstId = 0, mnId = 0, curId = -1;
	myObj *field;

	bool bStarted, bFinished;

	float TIME = 0, fLastTime = 0;
	Clock clock;
	RenderWindow *window;
	RectangleShape *recField;
	Font font;

	void update();
	void render();
	void handleEvent();
	void updateTime();
	void checkNext();
	void moveMn();
	void regen();


public:
	App(int _nScreenWidth, int _nScreenHeight, int _nFieldSize, int _nVisualSpeed);
	~App();
	void init();
	void run();
	double getFPS();
};
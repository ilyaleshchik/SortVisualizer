#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
using namespace sf;
#pragma once

class App {

private:
	int nScreenWidth, nScreenHeight;
	int nFieldSize;
	int nVisualSpeed = 0;
	int lstId = 0, mnId = 0, curId = -1;
	int *field;
	int way;
	std::mt19937 rnd;
	bool bStarted, bFinished;
	
	std::string fontName;

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
	void regen(bool isPermutation);


public:
	App() {}
	App(int _nScreenWidth, int _nScreenHeight, int _nFieldSize, int _nVisualSpeed, std::string _fontName);
	~App();
	void init();
	void run();
	double getFPS();
};
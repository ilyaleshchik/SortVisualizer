#include "sorting.h"
#include <iostream>
using namespace sf;

App::App(int _nScreenWidth, int _nScreenHeight, int _nFieldSize, int _nVisualSpeed, std::string _fontName) {

	nScreenHeight = _nScreenHeight;
	nScreenWidth = _nScreenWidth;
	nFieldSize = _nFieldSize;
	nVisualSpeed = _nVisualSpeed;
	TIME = 0; fLastTime = 0; way = 1;
	bFinished = 0;	
	bStarted = 0;
	rnd = std::mt19937(time(0));
	fontName = _fontName;
	
	field = new int[nFieldSize];
	for(int i = 0; i < nFieldSize; i++)
		field[i] = rnd() % 400 + 100;

	recField = new RectangleShape[nFieldSize];
	for(int i = 0; i < nFieldSize; i++) {
		recField[i] = RectangleShape(Vector2f(39, field[i]));
		recField[i].setFillColor(Color(117, 199, 139));
		recField[i].setPosition(i * 40, 700-field[i]);
	}
}

App::~App() {
	delete[] field;
	delete window;
}


void App::init() {
	//initialize
	window = new RenderWindow(VideoMode(nScreenWidth, nScreenHeight), "Sort");
	if (!font.loadFromFile(fontName)) {
		throw 228;
	}
}

void App::run() {

	while(!bFinished) {
		handleEvent();
		updateTime();
		if(TIME >= nVisualSpeed && bStarted)
			update();
		render();
	}

}
void App::regen(bool isPermutation = 0) {

	if (bStarted) return;
	if (isPermutation) {
		for (int i = 0; i < nFieldSize; i++) field[i] = (i + 1) * 25;
		std::shuffle(field, field + nFieldSize, rnd);
	}else
		for(int i = 0; i < nFieldSize; i++)
			field[i] = rnd() % 401 + 100;

	for(int i = 0; i < nFieldSize; i++) {
		recField[i] = RectangleShape(Vector2f(39, field[i]));
		recField[i].setFillColor(Color(117, 199, 139));
		recField[i].setPosition(i * 40, 700-field[i]);
	}
	lstId = 0; mnId = 0; curId = -1;
	bStarted = 0;
}

void App::handleEvent() {

	Event ev;
	while(window->pollEvent(ev)) {
		if(ev.type == Event::Closed)
			bFinished = 1;
		else if(ev.type == Event::KeyPressed) {
			if(ev.key.code == Keyboard::S) 
				bStarted = 1;
			else if(ev.key.code == Keyboard::R)
				regen();
			else if (ev.key.code == Keyboard::C && !bStarted) {
				way ^= 1;
			}
			else if (ev.key.code == Keyboard::P)
				regen(1);
		}
	}
}

void App::updateTime() {

	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	TIME += time / 500.0;	
}


void App::checkNext() {

	if (curId != lstId - 1 && curId != mnId)
		recField[curId].setFillColor(Color(117, 199, 139));
	curId++;
	if (curId == nFieldSize) return;
	recField[curId].setFillColor(Color(196, 237, 33));
	if (field[curId] <= field[mnId] && way) {
		recField[mnId].setFillColor(Color(117, 199, 139));
		mnId = curId;
		recField[mnId].setFillColor(Color(222, 126, 169));
	}
	else if (field[curId] >= field[mnId] && !way) {
		recField[mnId].setFillColor(Color(117, 199, 139));
		mnId = curId;
		recField[mnId].setFillColor(Color(222, 126, 169));
	}
}

void App::moveMn() {

	if(mnId == lstId) {
		recField[mnId].setFillColor(Color(117, 199, 139));
		return;
	}
	recField[mnId].setPosition(40 * (mnId - 1), 700 - field[mnId]);
	recField[mnId - 1].setPosition(40 * mnId, 700 - field[mnId - 1]);
	std::swap(field[mnId], field[mnId - 1]);
	std::swap(recField[mnId], recField[mnId - 1]);
	mnId--;
}

void App::update() {

	//sort alogithm
	TIME = 0;
	if(lstId == nFieldSize) {
		for (int i = 0; i < nFieldSize; i++) {
			recField[i] = RectangleShape(Vector2f(39, field[i]));
			recField[i].setFillColor(Color(117, 199, 139));
			recField[i].setPosition(i * 40, 700 - field[i]);
		}
		lstId = 0; mnId = 0; curId = -1;
		bStarted = 0;
		return;
	}

	if(curId != nFieldSize) {
		checkNext();
	}else if(mnId != lstId) {
		moveMn();
	}else {
		lstId++;
		mnId = lstId;
		curId = lstId - 1;
	}

}

void App::render() {

	window->clear(Color(255, 255, 255, 255));

	Text rules;

	rules.setFont(font);
	rules.setString("S - start\nR - regenerate numbers\nP - shuffle permutaion\nC - change sort order");
	rules.setCharacterSize(16);
	rules.setFillColor(Color::Black);
	
	rules.move(50, 50);
	window->draw(rules);

	for(int i = 0; i < nFieldSize; i++) {
		window->draw(recField[i]);
	}

	window->display();

}
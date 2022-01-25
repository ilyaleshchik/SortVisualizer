#include "sorting.h"
#include <iostream>
using namespace sf;

const std::string FONT = "Dongle-Regular.ttf";

App::App(int _nScreenWidth, int _nScreenHeight, int _nFieldSize, int _nVisualSpeed) {

	nScreenHeight = _nScreenHeight;
	nScreenWidth = _nScreenWidth;
	nFieldSize = _nFieldSize;
	nVisualSpeed = _nVisualSpeed;
	TIME = 0; fLastTime = 0;
	bFinished = 0;	
	bStarted = 0;

	if(!font.loadFromFile("ghotic.ttf")) {
		std::cerr << "Font load ERROR!!!!!";
		exit(0);
	}
	
	field = new myObj[nFieldSize];
	for(int i = 0; i < nFieldSize; i++)
		field[i] = myObj();

	recField = new RectangleShape[nFieldSize];
	for(int i = 0; i < nFieldSize; i++) {
		recField[i] = RectangleShape(Vector2f(39, field[i].nVal));
		recField[i].setFillColor(Color(117, 199, 139));
		recField[i].setPosition(i * 40, 700-field[i].nVal);
	}
}

App::~App() {
	delete[] field;
	delete window;
}


void App::init() {
	//initialize
	window = new RenderWindow(VideoMode(nScreenWidth, nScreenHeight), "BFS");
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
void App::regen() {

	if (bStarted) return;
	
	for(int i = 0; i < nFieldSize; i++)
		field[i] = myObj();

	for(int i = 0; i < nFieldSize; i++) {
		recField[i] = RectangleShape(Vector2f(39, field[i].nVal));
		recField[i].setFillColor(Color(117, 199, 139));
		recField[i].setPosition(i * 40, 700-field[i].nVal);
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
		}
	}
}

void App::updateTime() {

	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	TIME += time / 500.0;	
}


void App::checkNext() {
	
	if(curId != lstId - 1 && curId != mnId)
		recField[curId].setFillColor(Color(117, 199, 139));
	curId++;
	if(curId == nFieldSize) return;
	recField[curId].setFillColor(Color(196, 237, 33));
	if(field[curId].nVal <= field[mnId].nVal) {
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
	recField[mnId].setPosition(40 * (mnId - 1), 700 - field[mnId].nVal);
	recField[mnId - 1].setPosition(40 * mnId, 700 - field[mnId - 1].nVal);
	std::swap(field[mnId], field[mnId - 1]);
	std::swap(recField[mnId], recField[mnId - 1]);
	mnId--;
}

void App::update() {

	//sort alogithm
	TIME = 0;
	if(lstId == nFieldSize) {
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
	rules.setString("S - start\nR - regenerate numbers");
	rules.setCharacterSize(16);
	rules.setFillColor(Color::Black);
	
	rules.move(50, 50);
	window->draw(rules);

	for(int i = 0; i < nFieldSize; i++) {
		window->draw(recField[i]);
	}

	window->display();

}
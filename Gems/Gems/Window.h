#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Gem.h"
#include<iostream>

#define BOMB_DAMAGE 4
#define FIELD_SIZE 10
#define BONUS_RANGE 3
#define GEM_SIZE 80
#define OUTLINE_SIZE 5
#define TITLE "GEMS"

using namespace std;

struct Coordinate {
	int x, y;
	bool operator==(Coordinate c) {
		return x == c.x && c.y == y;
	}
	bool operator!=(Coordinate c) {
		return (x != c.x || c.y != y) ;
	}
};

struct cursorState {
	int x, y;
	bool isEmpty;
};


class Window
{
private:
	sf::RenderWindow* window;

	unsigned int height, width;
	cursorState state;

	vector <vector<Gem>> gems;
	vector<Coordinate> toDrop;
	vector <vector<Coordinate>> coordinates;

	void start();
	void mouseEvent(sf::Event);
	void drawField();
	bool checkField();
	void destroyField();

	void createCoordinates();
	void setAllPositions();
	void createAllGems();

	Gem* getGemByPosition(const Coordinate&);
	void dropColumn(const Coordinate&);
	void moveDown(Coordinate&);

	int randomInt(int from, int to);

public:
	Window(unsigned int width, unsigned int heigth);
	void live();
	bool isOpen();
};


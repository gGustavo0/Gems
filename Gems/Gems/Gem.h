#pragma once

#include <SFML/Graphics.hpp>

#define SIZE 35.f
#define OUTLINE_SIZE 5

using namespace std;

struct Position {
	short x, y;
};


class Gem
{
	float size = SIZE;
	float outlineSize = OUTLINE_SIZE;
	void setColor(int);
public:
	Gem();
	void setColor(const sf::Color &fillColor, const sf::Color &outlineColor);
	void setShapeColor(const sf::Color &fillColor, const sf::Color &outlineColor);
	void copy(const sf::Color &fillColor, const sf::Color &outlineColor);
	void exchange(Gem&);
	void randomColor();
	sf::Color fillColor;
	sf::Color outlineColor;
	Position position;
	sf::CircleShape shape;
	bool isNeibour(const Gem&) const;
	void copy(const Gem&);
};


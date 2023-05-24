#include "Gem.h"

void Gem::setColor(int color) {
	sf::Color fillColor(0, 0, 0);
	sf::Color outlineColor(0, 0, 0);

	switch (color)
	{
	case 0:
	{
		sf::Color fillTempRed(255, 0, 0);
		sf::Color outlineTempRed(128, 0, 0);
		fillColor = fillTempRed;
		outlineColor = outlineTempRed;
		break;
	}
	case 1:
	{
		sf::Color fillTempBlue(0, 0, 255);
		sf::Color outlineTempBlue(0, 0, 128);
		fillColor = fillTempBlue;
		outlineColor = outlineTempBlue;
		break;
	}
	case 2:
	{
		sf::Color fillTempYellow(250, 250, 0);
		sf::Color outlineTempYellow(255, 215, 0);
		fillColor = fillTempYellow;
		outlineColor = outlineTempYellow;
		break;
	}
	case 3:
	{
		sf::Color fillTempGreen(0, 255, 0);
		sf::Color outlineTempGreen(50, 205, 50);
		fillColor = fillTempGreen;
		outlineColor = outlineTempGreen;
		break;
	}
	case 4:
	{
		sf::Color fillTempWhite(255, 255, 255);
		sf::Color outlineTempWhite(220, 220, 220);
		fillColor = fillTempWhite;
		outlineColor = outlineTempWhite;
		break;
	}
	default:
		break;
	}

	copy(fillColor, outlineColor);
}

Gem::Gem() {
	shape = *new sf::CircleShape(size);
	shape.setOutlineThickness(outlineSize);
	randomColor();
}


void Gem::randomColor() {
	int number = rand();
	number = 0 + rand() % (4 - 0 + 1);
	setColor(number);
}

bool Gem::isNeibour(const Gem& gem) const{
	if ((abs(position.x - gem.position.x) == 1) && (abs(position.y - gem.position.y) == 0)) return true;
	if ((abs(position.x - gem.position.x) == 0) && (abs(position.y - gem.position.y) == 1)) return true;
	return false;
}

void Gem::setShapeColor(const sf::Color &fillColor, const sf::Color &outlineColor) {
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
}

void Gem::setColor(const sf::Color &fillColor, const sf::Color &outlineColor) {
	this->fillColor = fillColor;
	this->outlineColor = outlineColor;
}

void Gem::copy(const sf::Color &fillColor, const sf::Color &outlineColor) {
	setShapeColor(fillColor, outlineColor);
	setColor(fillColor, outlineColor);
}

void Gem::exchange(Gem& gem) {
	sf::Color fillColor = gem.fillColor;
	sf::Color outlineColor = gem.outlineColor;

	gem.setShapeColor(this->fillColor, this->outlineColor);
	setShapeColor(fillColor, outlineColor);

	swap(gem.fillColor, this->fillColor);
	swap(gem.outlineColor, this->outlineColor);
}

void Gem::copy(const Gem& gem) {
	copy(gem.fillColor, gem.outlineColor);
}
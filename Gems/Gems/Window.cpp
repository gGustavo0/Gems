#include "Window.h"

Window::Window(unsigned int width, unsigned int heigth) {
	this->width = width;
	this->height = heigth;
	window = new sf::RenderWindow(sf::VideoMode(width, heigth), TITLE, sf::Style::Close);
	window->setVerticalSyncEnabled(true);
	state.isEmpty = true;
	createCoordinates();
	start();
}

int Window::randomInt(int from, int to) {
	return from + rand() % (to - from + 1);
}

void Window::dropColumn(const Coordinate& coordinate) {
	for (int i = coordinate.y; i > 0; i--)
	{
		Coordinate c = { coordinate.x, i };
		moveDown(c);
	}
	gems[coordinate.x][0].randomColor();
}

bool Window::checkField() {
	bool isDestroy = false;
	for (int i = 0; i < FIELD_SIZE ; i++)
	{
		sf::Color color = gems[i][0].fillColor;
		int count = 1;
		for (int j = 1; j < FIELD_SIZE; j++) {
			if (gems[i][j].fillColor == color) {
				count++;
			}
			else
			{
				count = 1;
				color = gems[i][j].fillColor;
			}
			if (count > 3) {
				Coordinate c2 = { i, j };
				toDrop.push_back(c2);
			}
			if (count == 3) {
				Coordinate c = { i, j};
				Coordinate c1 = { i, j - 2 };
				Coordinate c2 = { i, j - 1 };
				toDrop.push_back(c1);
				toDrop.push_back(c2);
				toDrop.push_back(c);
				isDestroy = true;
			}
		}
	}

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		sf::Color color = gems[0][i].fillColor;
		int count = 1;
		for (int j = 1; j < FIELD_SIZE; j++) {
			if (gems[j][i].fillColor == color) {
				count++;
			}
			else
			{
				count = 1;
				color = gems[j][i].fillColor;
			}
			if (count > 3) {
				Coordinate c2 = { j, i };
				toDrop.push_back(c2);
			}
			if (count == 3) {
				Coordinate c2 = { j - 1, i };
				Coordinate c1 = { j - 2, i };
				Coordinate c = { j, i };
				if (std::find(toDrop.begin(), toDrop.end(), c1) == toDrop.end()) toDrop.push_back(c1);
				if (std::find(toDrop.begin(), toDrop.end(), c2) == toDrop.end() ) toDrop.push_back(c2);
				if (std::find(toDrop.begin(), toDrop.end(), c) == toDrop.end()) toDrop.push_back(c);
				isDestroy = true;
			}
		}
	}
	return isDestroy;
}

void Window::destroyField() {
	for (auto &i: toDrop)
	{
		int type = randomInt(0, 100);

		int fromX = abs((int)i.x - BONUS_RANGE); int toX = i.x + BONUS_RANGE;
		int fromY = abs((int)(i.y - BONUS_RANGE)); int toY = i.y + BONUS_RANGE;
		if (toX > (FIELD_SIZE - 1)) toX = (FIELD_SIZE - 1); if (toY > (FIELD_SIZE - 1)) toY = (FIELD_SIZE - 1);
		
		int x = randomInt(fromX, toX);
		int y = randomInt(fromY, toY);

		if (type % 10 == 0) { //bomb
			Coordinate destination = { x, y };
			dropColumn(destination);
			for (int i = 0; i < BOMB_DAMAGE; i++)
			{
				int x = randomInt(0, FIELD_SIZE - 1);
				int y = randomInt(0, FIELD_SIZE - 1);

				Coordinate destination = { x, y };
				dropColumn(destination);
			}
			cout << "BOMB" << endl;
		}
		if (type % 10 == 1) { //cross
			gems[x][y].copy(gems[i.x][i.y]);

			int neibourX = randomInt(0, 1);
			int neibourY = randomInt(0, 1);
			if (neibourX == 0) neibourX = -1; else neibourX = 1;
			if (neibourY == 0) neibourY = -1; else neibourY = 1;
			
			int firstDestY = y + neibourY; int firstDestX = x + neibourX;
			int secondDestY = y - neibourY; int secondDestX = x - neibourX;

			if ((firstDestY > FIELD_SIZE - 1) || (firstDestY < 0))
			{
				firstDestY = y - neibourY;
			}

			if ((firstDestX > FIELD_SIZE - 1) || (firstDestX < 0))
			{
				firstDestX = x - neibourX;
			}

			if ((secondDestY > FIELD_SIZE - 1) || (secondDestY < 0))
			{
				secondDestY = y + neibourY;
			}

			if ((secondDestX > FIELD_SIZE - 1) || (secondDestX < 0))
			{
				secondDestX = x + neibourX;
			}

			gems[firstDestX][firstDestY].copy(gems[i.x][i.y]);
			gems[secondDestX][secondDestY].copy(gems[i.x][i.y]);
			cout << "CROSS" << endl;
		}
		dropColumn(i);
	}
	toDrop.clear();
}


void Window::createCoordinates() {
	coordinates.resize(FIELD_SIZE + 1);
	for (int i = 0; i < coordinates.size(); i++)
	{
		coordinates[i].resize(FIELD_SIZE + 1);
		for (int j = 0; j < coordinates[i].size(); j++)
		{
			coordinates[i][j].x = GEM_SIZE * i;
			coordinates[i][j].y = GEM_SIZE * j;
		}
	}
}

void Window::setAllPositions() {
	for (int i = 0; i < gems.size(); i++)
	{
		for (int j = 0; j < gems[i].size(); j++) {
			gems[i][j].position.x = i;
			gems[i][j].position.y = j;
			gems[i][j].shape.setPosition((float)(coordinates[i][j].x + OUTLINE_SIZE), (float)(coordinates[i][j].y + OUTLINE_SIZE));
		}
	}
}

void Window::drawField() {
	window->clear(sf::Color::Black);
	for (auto &i: gems) {
		for (auto &j : i)
		{
			window->draw(j.shape);
		}
	}
	window->display();
}

void Window::createAllGems() {
	gems.resize(FIELD_SIZE);
	for (auto& i : gems)
	{
		i.resize(FIELD_SIZE);
		for (auto& j : i)
		{
			j = *new Gem();
		}
	}
}

void Window::start() {
	srand(unsigned(time(0)));
	createAllGems();
	createCoordinates();
	setAllPositions();
	drawField();
	while (checkField()) destroyField();
}


bool Window::isOpen() { return window->isOpen(); }

Gem* Window::getGemByPosition(const Coordinate &position){
	int i = 0;
	while (!(position.x >= coordinates[i][0].x && position.x <= coordinates[i + 1][0].x)) {
		i++;
	}
	int j = 0;
	while (!(position.y >= coordinates[0][j].y && position.y <= coordinates[0][j + 1].y)) {
		j++;
	}
	return &gems[i][j];
}

void Window::moveDown(Coordinate& coordinate) {
	if (coordinate.y == 0)
	{
		return;
	}
	gems[coordinate.x][coordinate.y].copy(gems[coordinate.x][coordinate.y - 1]);
	drawField();
}


void Window::mouseEvent(sf::Event event) {
	if (state.isEmpty) {
		state.x = event.mouseButton.x;
		state.y = event.mouseButton.y;
		state.isEmpty = false;
	}
	else
	{
		Coordinate position1 = {state.x, state.y};
		Coordinate position2 = {event.mouseButton.x, event.mouseButton.y};
		Gem *g1 = getGemByPosition(position1);
		Gem* g2 = getGemByPosition(position2);
		if (g1->isNeibour(*g2)) {
			g1->exchange(*g2);
			if (checkField()) { 
				destroyField(); 
				while (checkField()) destroyField();
			}
			else g1->exchange(*g2);
		}
		
		state.isEmpty = true;
		drawField();
	}
}

void Window::live() {
	start();
	//main loop
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonReleased:
				mouseEvent(event);
				break;
			default:
				break;
			}

		}
	}

}
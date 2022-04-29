#include "Door.hpp"

using namespace sf;

Door::Door(bool isHorizontal, float x, float y)
{
	this->horizontal = isHorizontal;

	Vector2f s;

	if (isHorizontal) {
		s = Vector2f(DOOR_SIZE, WALL_THICKNESS);
	}

	else {
		s = Vector2f(WALL_THICKNESS, DOOR_SIZE);
	}

	this->entity = RectangleShape(s);
	this->entity.setFillColor(Color::Green);
	this->entity.setPosition(x, y);

	this->bounds = Bounds(y, y + s.y, x, x + s.x);
}

bool Door::isHorizontal()
{
	return this->horizontal;
}

void Door::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

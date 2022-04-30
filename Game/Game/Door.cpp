#include "Door.hpp"

using namespace sf;

Door::Door(bool isHorizontal, Position p)
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
	this->entity.setPosition(p.x, p.y);

	this->bounds = Bounds(p.y, p.y + s.y, p.x, p.x + s.x);
}

bool Door::isHorizontal()
{
	return this->horizontal;
}

void Door::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

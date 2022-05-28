#include "Door.hpp"

Door::Door(bool horizontal, Position p) : RectangleEntity(DOOR_SIZE, WALL_THICKNESS, DOOR_COLOR)
{
	this->horizontal = horizontal;

	if (horizontal) {
		this->setPosition({ p.x + DOOR_SIZE / 2, p.y + WALL_THICKNESS / 2 });
	}
	else {
		this->transpose();
		this->setPosition({ p.x + WALL_THICKNESS / 2, p.y + DOOR_SIZE / 2 });
	}
}

bool Door::isHorizontal() const
{
	return this->horizontal;
}

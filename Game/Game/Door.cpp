#include "Door.hpp"

using namespace sf;

Door::Door(bool horizontal, float size, float wallThickness, sf::Vector2f position): horizontal(horizontal), size(size)
{
	Vector2f s;

	if (horizontal) {
		s = Vector2f(size, wallThickness);
	}

	else {
		s = Vector2f(wallThickness, size);
	}

	this->entity = RectangleShape(s);
	this->entity.setFillColor(Color::Green);
	this->entity.setPosition(position);

	this->bounds = this->entity.getGlobalBounds();

	if (horizontal) {
		this->minBound = this->bounds.left;
		this->maxBound = this->bounds.left + this->bounds.width;
	}
	else
	{
		this->minBound = this->bounds.top;
		this->maxBound = this->bounds.top + this->bounds.height;
	}
}

bool Door::isHorizontal()
{
	return this->horizontal;
}

float Door::getMinBound()
{
	return this->minBound;
}

float Door::getMaxBound()
{
	return this->maxBound;
}

bool Door::inDoorRange(sf::FloatRect rect)
{
	if (this->horizontal) {
		return this->minBound < rect.left && this->maxBound > rect.left + rect.width;
	}
	else {
		return this->minBound < rect.top && this->maxBound > rect.top + rect.height;
	}
}

sf::FloatRect Door::getBounds()
{
	return this->bounds;
}

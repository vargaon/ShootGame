#pragma once

#include "Entity.hpp"

using namespace sf;

MoveableEntity::MoveableEntity(float size, int pointCount, sf::Color color, sf::Vector2f position, int direction): size(size), x(position.x), y(position.y), direction(direction)
{
	this->entity = CircleShape(size, pointCount);
	this->entity.setFillColor(color);
	this->entity.setOrigin(Vector2f(size, size));
}

sf::FloatRect MoveableEntity::getBounds()
{
	return sf::FloatRect(this->x - this->size, this->y - this->size, this->size *2, this->size*2);
}

sf::Vector2f MoveableEntity::getPosition()
{
	return sf::Vector2f(this->x, this->y);
}

sf::Vector2f MoveableEntity::computeDirectionsPowers()
{
	return Vector2f(cos(this->direction * DEGTORAD), sin(this->direction * DEGTORAD));
}

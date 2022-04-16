#pragma once

#include "Entity.hpp"

using namespace sf;

Entity::Entity(float size, int nVertices, sf::Color color, sf::Vector2f position, int angle): size(size), x(position.x), y(position.y), angle(angle)
{
	this->entity = CircleShape(size, nVertices);
	this->entity.setFillColor(color);
	this->entity.setOrigin(Vector2f(size, size));
	
	this->x = position.x;
	this->y = position.y;
}

sf::Vector2f Entity::computeDirectionsPowers()
{
	return Vector2f(cos(this->angle * DEGTORAD), sin(this->angle * DEGTORAD));
}

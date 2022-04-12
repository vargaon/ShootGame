#pragma once

#include "Entity.hpp"

using namespace sf;

void Entity::setStartPosition(sf::Vector2f pos)
{
	this->x = pos.x;
	this->y = pos.y;
}

void Entity::initEntity(float size, int nVertices, sf::Color color)
{
	this->size = size;

	this->entity = CircleShape(size, nVertices);
	this->entity.setFillColor(color);
	this->entity.setOrigin(Vector2f(size, size));
}

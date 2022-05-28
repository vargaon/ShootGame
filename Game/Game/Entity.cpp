#pragma once
#include "Entity.hpp"

using namespace sf;

Bounds Entity::getBounds() const
{
	return this->bounds;
}

Position Entity::getPosition() const
{
	return this->position;
}

void Entity::transpose()
{
	auto temp = this->width;
	this->width = this->height;
	this->height = temp;

	this->bounds = Bounds(this->width, this->height, this->position);
}

void Entity::updatePosition(Position p)
{
	this->position = p;
	this->bounds.updateByPosition(p);
}

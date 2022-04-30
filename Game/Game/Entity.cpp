#pragma once
#include "Entity.hpp"

using namespace sf;

Entity::Entity(float size, int pointCount, sf::Color color) : size(size)
{
	this->entity = CircleShape(size, pointCount);
	this->entity.setFillColor(color);
	this->entity.setOrigin(size, size);
}

void Entity::setPosition(float x, float y)
{
	this->entity.setPosition(x, y);
}

void Entity::setRotation(float direction)
{
	this->entity.setRotation(direction);
}

Bounds Entity::getBounds(float x, float y)
{
	return Bounds(y - this->size, y + this->size, x - this->size, x + this->size);
}

void Entity::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

void MoveableEntity::computeDirectionsPowers(float d)
{
	this->dx = cos(d * float(PI) / 180);
	this->dy = sin(d * float(PI) / 180);
}

Bounds MoveableEntity::getBounds()
{
	return Bounds(this->y - this->size, this->y + this->size, this->x - this->size, this->x + this->size);
}

void MoveableEntity::setStartPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	this->setPosition(x, y);
}

float MoveableEntity::getDirection()
{
	return this->direction;
}

void MoveableEntity::setDirection(float direction)
{
	this->direction = direction;
	this->setRotation(direction + 90.f);
	this->computeDirectionsPowers(direction);
}

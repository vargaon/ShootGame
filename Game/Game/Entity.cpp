#pragma once
#include "Entity.hpp"

using namespace sf;

Entity::Entity(float size, int pointCount, sf::Color color) : size(size)
{
	this->entity = CircleShape(size, pointCount);
	this->entity.setFillColor(color);
	this->entity.setOrigin(Vector2f(size, size));
}

Bounds Entity::getBounds()
{
	return Bounds(this->y - this->size, this->y + this->size, this->x - this->size, this->x + this->size);
}

void Entity::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Entity::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

void MoveableEntity::computeDirectionsPowers(float d)
{
	this->dx = cos(d * DEGTORAD);
	this->dy = sin(d * DEGTORAD);
}

float MoveableEntity::getDirection()
{
	return this->direction;
}

void MoveableEntity::setDirection(float direction)
{
	this->direction = direction;
	this->computeDirectionsPowers(direction);
}

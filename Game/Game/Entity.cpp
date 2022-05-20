#pragma once
#include "Entity.hpp"

using namespace sf;

Entity::Entity(float size, unsigned int pointCount, sf::Color color) : size(size)
{
	this->entity = CircleShape(size, pointCount);
	this->entity.setFillColor(color);
	this->entity.setOrigin(size, size);
}

void Entity::setPosition(Position p)
{
	this->position = p;
	this->bounds = Bounds(p.y - this->size, p.y + this->size, p.x - this->size, p.x + this->size);

	this->entity.setPosition(p.x, p.y);
}

void Entity::setRotation(float direction)
{
	this->entity.setRotation(direction);
}

Bounds Entity::getBounds() const
{
	return this->bounds;
}

Position Entity::getPosition() const
{
	return this->position;
}

void Entity::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

float MoveableEntity::getDirection() const
{
	return this->direction;
}

void MoveableEntity::setDirection(float dir)
{
	this->direction = dir;
	this->setRotation(dir + 90.f);
	this->computeDirectionsPowers();
}

void MoveableEntity::computeDirectionsPowers()
{
	this->dx = cos(this->direction * float(PI) / 180);
	this->dy = sin(this->direction * float(PI) / 180);
}

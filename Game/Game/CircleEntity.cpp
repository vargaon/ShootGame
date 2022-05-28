#include "CircleEntity.hpp"

CircleEntity::CircleEntity(float size, unsigned int pointCount, sf::Color color) : Entity(size * 2 , size * 2)
{
	this->size = size;

	this->entity.setRadius(size);
	this->entity.setOrigin(size, size);
	this->entity.setPointCount(pointCount);
	this->entity.setFillColor(color);
}

void CircleEntity::drawAt(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

float CircleEntity::getSize()
{
	return this->size;
}

void CircleEntity::setPosition(Position p)
{
	this->updatePosition(p);
	this->entity.setPosition(p.x, p.y);
}

void CircleEntity::setRotation(float direction)
{
	this->entity.setRotation(direction);
}

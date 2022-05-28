#include "RectangleEntity.hpp"

RectangleEntity::RectangleEntity(float width, float height, sf::Color color) : Entity(width, height)
{
	this->entity.setSize({ width, height });
	this->entity.setOrigin({ width / 2, height / 2 });
	this->entity.setFillColor(color);
}

void RectangleEntity::transpose()
{
	Entity::transpose();
	this->entity.setRotation(90);
}

void RectangleEntity::drawAt(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

void RectangleEntity::setPosition(Position p)
{
	this->updatePosition(p);
	this->entity.setPosition(p.x, p.y);
}

#include "Item.hpp"

Item::Item(float x, float y) : Entity(ITEM_SIZE, ITEM_POINT_COUNT, sf::Color::Yellow)
{
	this->setPosition(x, y);
	this->bounds = this->getBounds(x, y);
}

void Item::collect()
{
	this->active = false;
}

bool Item::isActive()
{
	return active;
}

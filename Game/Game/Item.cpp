#include "Item.hpp"

Item::Item(float x, float y) : Entity(ITEM_SIZE, ITEM_POINT_COUNT, sf::Color::Yellow)
{
	this->setPosition(x, y);
	this->bounds = this->getBounds(x, y);
}

void Item::update()
{
	if (!this->active) return;

	if (this->activeCooldownClock.getElapsedTime().asMilliseconds() > ITEM_ACTIVE_COOLDOWN) {
		this->active = false;
	}
}

void Item::collect()
{
	this->active = false;
}

bool Item::isActive()
{
	return active;
}

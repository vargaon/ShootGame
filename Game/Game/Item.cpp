#include "Item.hpp"

Item::Item(Position p) : Entity(ITEM_SIZE, ITEM_POINT_COUNT, sf::Color::Yellow)
{
	this->setPosition(p);
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

bool Item::isActive() const
{
	return active;
}

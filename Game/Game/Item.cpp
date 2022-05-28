#include "Item.hpp"

Item::Item(Position p) : CircleEntity(ITEM_SIZE, ITEM_POINT_COUNT, ITEM_COLOR)
{
	this->setPosition(p);
}

bool Item::isActive() const
{
	return active;
}

bool Item::tryCollect(Bounds bounds)
{
	if (!this->active) return false;

	if (this->getBounds().inCollisionWith(bounds)) {
		this->active = false;

		return true;
	}

	return false;
}

void Item::update()
{
	if (!this->active) return;

	if (this->activeCooldownClock.getElapsedTime().asMilliseconds() > ITEM_ACTIVE_COOLDOWN) {
		this->active = false;
	}
}

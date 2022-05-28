#include "Coin.hpp"

Coin::Coin(Position p) : CircleEntity(COIN_SIZE, COIN_POINT_COUNT, COIN_COLOR)
{
	this->setPosition(p);
}

bool Coin::isActive() const
{
	return active;
}

bool Coin::tryCollect(const Bounds& b)
{
	if (!this->active) return false;

	if (this->getBounds().inCollisionWith(b)) {
		this->active = false;

		return true;
	}

	return false;
}

void Coin::update()
{
	if (!this->active) return;

	if (this->activeCooldownClock.getElapsedTime().asMilliseconds() > COIN_ACTIVE_COOLDOWN) {
		this->active = false;
	}
}

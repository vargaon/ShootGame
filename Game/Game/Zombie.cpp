#include "Zombie.hpp"

bool Zombie::isAlive() const
{
	return this->alive;
}

void Zombie::die()
{
	this->alive = false;
}

void Zombie::update(Map& map)
{
	if (!this->alive) return;

	this->move(map, ZOMBIE_MOVE_SPEED);
}

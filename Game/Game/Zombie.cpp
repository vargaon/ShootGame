#include "Zombie.hpp"

void Zombie::update(Map& m)
{
	if (!this->alive) return;

	if (this->movePower == PersonMovePower::FORWARD) {

		this->x += this->dx * ZOMBIE_MOVE_SPEED;
		this->y += this->dy * ZOMBIE_MOVE_SPEED;

		this->setPosition({this->x, this->y});

		this->moveInDoors(m.doors);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms);
		}
	}
}

bool Zombie::isAlive() const
{
	return this->alive;
}

void Zombie::die()
{
	this->alive = false;
}

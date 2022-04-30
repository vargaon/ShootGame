#include "Zombie.hpp"

void Zombie::checkForBulletes(bulletes_con_t& bulletes)
{
	auto bounds = this->getBounds();

	for (auto&& b : bulletes) {

		if (!b.isActive()) {
			continue;
		}

		auto bb = b.getBounds();
		if (bounds.inCollisionWith(bb)) {
			this->alive = false;
			b.destroy();
			return;
		}
	}
}

void Zombie::checkForPlayer(Player& p)
{
	auto bounds = this->getBounds();

	auto pb = p.getBounds();

	if (bounds.inCollisionWith(pb)) {

		p.hurt();
		this->alive = false;
	}
	else {

		auto playerPosition = p.getPosition();
		this->setDirectionByPosition(playerPosition.x, playerPosition.y);
	}
}

void Zombie::update(Map& m, Player& p, bulletes_con_t& bulletes)
{
	this->checkForBulletes(bulletes);
	this->checkForPlayer(p);

	if (!this->alive) return;

	if (this->movePower == PersonMovePower::FORWARD) {

		this->x += this->dx * ZOMBIE_MOVE_SPEED;
		this->y += this->dy * ZOMBIE_MOVE_SPEED;

		this->bounds = this->getBounds();

		this->moveInDoors(m.doors);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms);
		}
	}

	this->setPosition(this->x, this->y);
}

bool Zombie::isAlive()
{
	return this->alive;
}

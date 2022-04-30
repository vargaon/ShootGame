#include "Zombie.hpp"

void Zombie::checkForBulletes(bulletes_con_t& bulletes)
{
	for (auto&& b : bulletes) {

		if (!b.isActive()) {
			continue;
		}

		auto bb = b.getBounds();

		if (this->bounds.inCollisionWith(bb)) {

			this->alive = false;
			b.destroy();
			return;
		}
	}
}

void Zombie::checkForPlayer(Player& p)
{
	auto pb = p.getBounds();

	if (this->bounds.inCollisionWith(pb)) {

		p.hurt();
		this->alive = false;
	}
	else {

		auto playerPosition = p.getPosition();
		this->setDirectionByPosition(playerPosition);
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

		Position p(this->x, this->y);
		this->setPosition(p);

		this->moveInDoors(m.doors);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms);
		}
	}
}

bool Zombie::isAlive()
{
	return this->alive;
}

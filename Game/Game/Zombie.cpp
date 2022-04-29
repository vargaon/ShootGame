#include "Zombie.hpp"

void Zombie::checkForBulletes(bulletes_con_t& bulletes)
{
	auto bounds = this->getBounds();

	for (auto&& b : bulletes) {
		auto bb = b.getBounds();
		if (bounds.inCollisionWith(bb)) {
			this->alive = false;
			b.destroy();
			return;
		}
	}
}

void Zombie::update(Map& m, Player& p, bulletes_con_t& bulletes)
{
	this->checkForBulletes(bulletes);

	if (!this->alive) return;

	auto playerPosition = p.getPosition();

	this->setDirectionByPosition(playerPosition.x, playerPosition.y);

	if (this->movePower == PersonMovePower::FORWARD) {

		this->x += this->dx * PLAYER_MOVE_SPEED;
		this->y += this->dy * PLAYER_MOVE_SPEED;

		this->moveInDoors(m.doors);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms);
		}
	}

	this->entity.setPosition(this->x, this->y);
	this->entity.setRotation(this->getDirection() + 90.f);
}

bool Zombie::isAlive()
{
	return this->alive;
}

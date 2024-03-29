#include "Bullet.hpp"

bool Bullet::isActive()
{
	return this->active;
}

void Bullet::setStartPosition(Position p)
{
	this->x = p.x;
	this->y = p.y;

	this->setPosition(p);
}

void Bullet::destroy()
{
	this->active = false;
}

void Bullet::update(const Map& m)
{
	if (!this->active) return;

	float moveX = this->dx * BULLET_MOVE_SPEED / BULLET_SPLIT_FRAME_COUNT;
	float moveY = this->dy * BULLET_MOVE_SPEED / BULLET_SPLIT_FRAME_COUNT;

	for (int i = 0; i < BULLET_SPLIT_FRAME_COUNT; i++) {

		this->x += moveX;
		this->y += moveY;

		Position p(this->x, this->y);
		this->setPosition(p);

		this->moveInDoors(m.doors);

		if (!this->inDoor && this->active) {
			this->moveInRooms(m.rooms);
		}

		if (!this->active) break;
	}
}

void Bullet::moveInRooms(const rooms_con_t& rooms)
{
	const auto& bulletBounds = this->getBounds();

	for (auto&& roomRow : rooms) {

		for (auto&& r : roomRow) {
			if (bulletBounds.isIn(r.getOuterBounds())) {

				this->active = bulletBounds.isIn(r.getInnerBounds());
				return;
			}
		}
	}

	this->active = false;
}

void Bullet::moveInDoors(const doors_con_t& doors)
{
	const auto& bulletBounds = this->getBounds();

	for (auto&& d : doors) {

		if (bulletBounds.inCollisionWith(d.getBounds())) {

			this->inDoor = true;
			this->active = bulletBounds.inRange(d.isHorizontal(), d.getBounds());

			return;
		}
	}

	this->inDoor = false;
}

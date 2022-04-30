#include "Bullet.hpp"

using namespace sf;

void Bullet::moveInRooms(rooms_con_t& rooms)
{
	for (auto&& r : rooms) {

		if (this->bounds.isIn(r.outerBounds)) {

			this->active = this->bounds.isIn(r.innerBounds);
			return;
		}
	}

	this->active = false;
}

void Bullet::moveInDoors(doors_con_t& doors)
{
	for (auto&& d : doors) {

		if (this->bounds.inCollisionWith(d.bounds)) {

			this->inDoor = true;
			this->active = this->bounds.inRange(d.isHorizontal(), d.bounds);

			return;
		}
	}

	this->inDoor = false;
}

bool Bullet::isActive()
{
	return this->active;
}

void Bullet::update(Map& m)
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

void Bullet::destroy()
{
	this->active = false;
}

void Bullet::setStartPosition(Position& p)
{
	this->x = p.x;
	this->y = p.y;

	this->setPosition(p);
}

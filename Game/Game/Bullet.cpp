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

		this->bounds = this->getBounds();

		this->moveInDoors(m.doors);

		if (!this->inDoor && this->active) {
			this->moveInRooms(m.rooms);
		}
		
		if (!this->active) break;
	}

	this->setPosition(this->x, this->y);
}

void Bullet::destroy()
{
	this->active = false;
}

void Bullet::setStartPosition(float x, float y)
{
	this->x = x;
	this->y = y;

	this->setPosition(x, y);
}

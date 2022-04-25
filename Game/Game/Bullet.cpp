#include "Bullet.hpp"

using namespace sf;

void Bullet::moveThroughDoors(doors_con_t doors)
{
	auto bounds = this->getBounds();

	for (auto&& d : doors) {

		auto d_bounds = d.getBounds();

		if (bounds.intersects(d_bounds) && d.inDoorRange(bounds)) {
			this->inDoor = true;
			return;
		}
	}

	this->inDoor = false;
}

void Bullet::moveInRooms(rooms_con_t rooms)
{
	if (this->inDoor) return;

	auto bounds = this->getBounds();

	for (auto&& r : rooms) {
		if (r.inLocalBounds(bounds)) return;
	}

	this->active = false;
}

void Bullet::update(rooms_con_t& rooms, doors_con_t& doors)
{
	if (!this->active) return;

	float movePartX = this->dx * BULLET_MOVE_SPEED / BULLET_SPLIT_FRAME_COUNT;
	float movePartY = this->dy * BULLET_MOVE_SPEED / BULLET_SPLIT_FRAME_COUNT;

	for (int i = 0; i < BULLET_SPLIT_FRAME_COUNT; i++) {

		this->x += movePartX;
		this->y += movePartY;

		this->moveThroughDoors(doors);
		this->moveInRooms(rooms);

		if (!this->active) break;
	}

	this->entity.setPosition(Vector2f(this->x, this->y));
}

void Bullet::setStartDirection(int direction)
{
	this->direction = direction;

	auto p_directions = computeDirectionsPowers();
	
	this->dx = p_directions.x;
	this->dy = p_directions.y;
}

bool Bullet::isActive()
{
	return this->active;
}

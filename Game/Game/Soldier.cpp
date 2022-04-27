#include "Soldier.hpp"
#include <iostream>

using namespace sf;

void Soldier::shoot(bulletes_con_t& bulletes)
{
	if (this->nBulletes > 0 && !this->reloading) {

		if (this->shootClock.getElapsedTime().asMilliseconds() > SOLDIER_SHOOT_COOLDOWN) {

			this->shootClock.restart();

			Bullet b;

			b.setStartPosition(Vector2f(this->x, this->y));
			b.setStartDirection(this->direction);

			bulletes.push_back(b);

			this->nBulletes--;

			if (this->nBulletes == 0) {
				this->reload();
			}
		}
	}
}

void Soldier::reload()
{
	this->reloading = true;
	this->reloadClock.restart();
}

void Soldier::update(rooms_con_t& rooms, doors_con_t& doors)
{

	if (this->reloading && this->reloadClock.getElapsedTime().asMilliseconds() > SOLDIER_RELOAD_COOLDOWN) {
		this->reloading = false;
		this->nBulletes = SOLDIER_BULLETES_NUMBER;
	}

	auto p_directions = computeDirectionsPowers();

	this->x += p_directions.x * int(this->movePower) * SOLDIER_MOVE_SPEED;
	this->y += p_directions.y * int(this->movePower) * SOLDIER_MOVE_SPEED;

	this->moveThroughDoors(doors);
	this->moveInRooms(rooms);

	this->entity.setPosition(Vector2f(this->x, this->y));
	this->entity.setRotation(this->direction + 90.f);
}

void Soldier::moveThroughDoors(doors_con_t doors)
{
	auto bounds = this->getBounds();

	bool state = false;

	for (auto&& d : doors) {

		auto d_bounds = d.getBounds();

		if (bounds.intersects(d_bounds)) {

			if (this->inDoor) {

				this->updateByDoor(d);
				state = true;
				break;
			}

			else {

				if (d.inDoorRange(bounds)) {

					this->inDoor = true;
					state = true;
				}

				break;
			}
		}
	}

	if (!state) this->inDoor = false;
}

void Soldier::moveInRooms(rooms_con_t rooms)
{
	if (this->inDoor) return;

	auto bounds = this->getBounds();

	for (auto&& r : rooms) {
		if (r.inRoom(bounds)) {
			this->updateByRoom(r);
			break;
		}
	}
}

void Soldier::updateByRoom(Room& room)
{
	auto bounds = room.getLocalBounds();

	float roomLeft = bounds.left;
	float roomRight = bounds.left + bounds.width;
	float roomTop = bounds.top;
	float roomBot = bounds.top + bounds.height;

	if (this->x - this->size < roomLeft) {
		this->x = roomLeft + this->size;
	}

	if (this->x + this->size > roomRight) {
		this->x = roomRight - this->size;
	}

	if (this->y - this->size < roomTop) {
		this->y = roomTop + this->size;
	}

	if (this->y + this->size > roomBot) {
		this->y = roomBot - this->size;
	}
}

void Soldier::updateByDoor(Door& door)
{
	if (door.isHorizontal()) {
		if (this->x - this->size < door.getMinBound()) {
			this->x = door.getMinBound() + this->size;
		}

		if (this->x + this->size > door.getMaxBound()) {
			this->x = door.getMaxBound() - this->size;
		}
	}
	else {
		if (this->y - this->size < door.getMinBound()) {
			this->y = door.getMinBound() + this->size;
		}

		if (this->y + this->size > door.getMaxBound()) {
			this->y = door.getMaxBound() - this->size;
		}
	}
}
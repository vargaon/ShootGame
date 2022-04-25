#pragma once

#include <iostream>
#include "Entity.hpp"

const int BULLET_MOVE_SPEED = 10;

const float BULLET_SIZE = 2.f;
const int BULLET_POINT_COUNT = 30;

const int BULLET_SPLIT_FRAME_COUNT = 2;

class Bullet : public MoveableEntity {

private:

	float dx, dy;
	bool active;

	void moveThroughDoors(doors_con_t doors) override;
	void moveInRooms(rooms_con_t rooms) override;

public:

	Bullet(sf::Vector2f position, int direction);

	bool isActive();

	void update(rooms_con_t& rooms, doors_con_t& doors) override;
};
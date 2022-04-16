#pragma once

#include <iostream>

#include "Entity.hpp"
#include "Door.hpp"
#include "Room.hpp"

const int BULLET_MOVE_SPEED = 10;

const float BULLET_SIZE = 2.f;
const int BULLET_POINT_COUNT = 30;

const int BULLET_SPLIT_FRAME_COUNT = 2;

class Bullet : public MoveableEntity {

private:

	float dx, dy;
	bool active;

	bool movementThroughDoor(doors_con_t doors);
	void movementInRoom(rooms_con_t rooms);

public:

	Bullet(sf::Vector2f position, int direction);

	void update(rooms_con_t& rooms, doors_con_t& doors);
	void render(sf::RenderWindow& window);

	bool isActive();
};
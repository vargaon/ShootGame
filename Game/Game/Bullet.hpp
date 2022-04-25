#pragma once

#include <iostream>
#include <vector>
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

	Bullet() : MoveableEntity(BULLET_SIZE, BULLET_POINT_COUNT, sf::Color::Black), active(true), dx(0.f), dy(0.f) {};

	bool isActive();

	void update(rooms_con_t& rooms, doors_con_t& doors);

	void setStartDirection(int direction);
	
};

using bulletes_con_t = std::vector<Bullet>;
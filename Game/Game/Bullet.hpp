#pragma once

#include <iostream>
#include <vector>

#include "MoveableEntity.hpp"
#include "Map.hpp"

const int BULLET_MOVE_SPEED = 10;
const float BULLET_SIZE = 2.f;
const int BULLET_POINT_COUNT = 30;
const int BULLET_SPLIT_FRAME_COUNT = 4;
const sf::Color BULLET_COLOR = { 0, 0, 0, 255 };

class Bullet : public MoveableEntity {

public:

	Bullet() : MoveableEntity(BULLET_SIZE, BULLET_POINT_COUNT, BULLET_COLOR) {};

	bool isActive();
	void setStartPosition(Position p);
	void destroy();
	void update(const Map& m);
	
private:

	bool active = true;

	void moveInRooms(const rooms_con_t& rooms);
	void moveInDoors(const doors_con_t& doors);
};

using bulletes_con_t = std::vector<Bullet>;
#pragma once
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Map.hpp"

const int BULLET_MOVE_SPEED = 10;
const float BULLET_SIZE = 2.f;
const int BULLET_POINT_COUNT = 30;
const int BULLET_SPLIT_FRAME_COUNT = 2;

class Bullet : public MoveableEntity {

private:

	bool active = true;

	void moveInRooms(rooms_con_t& rooms);
	void moveInDoors(doors_con_t& doors);

public:

	Bullet() : MoveableEntity(BULLET_SIZE, BULLET_POINT_COUNT, sf::Color::Black) {};

	bool isActive();
	void update(Map& m);
	void destroy();

	void setStartPosition(Position& p);
};

using bulletes_con_t = std::vector<Bullet>;
#pragma once

#include "Entity.hpp"
#include "Bullet.hpp"

const float SOLDIER_MOVE_SPEED = 1.f;
const int SOLDIER_TURN_SPEED = 3;
const float SOLDIER_SIZE = 10.f;
const int SOLDIER_POINT_COUNT = 3;
const int SOLDIER_SHOOT_COOLDOWN = 50;

enum class SoldierMove {
	FORWARD = 1,
	BACKWARD = -1,
	STOP = 0
};

class Soldier : public MoveableEntity {

protected:

	SoldierMove move = SoldierMove::STOP;
	sf::Clock clock;

	void updateByDoor(Door& door);
	void updateByRoom(Room& room);

	void moveThroughDoors(doors_con_t doors);
	void moveInRooms(rooms_con_t rooms);

public:

	Soldier(sf::Color color) : MoveableEntity(SOLDIER_SIZE, SOLDIER_POINT_COUNT, color) {};

	void shoot(bulletes_con_t& bulletes);

	void update(rooms_con_t& rooms, doors_con_t& doors);
};
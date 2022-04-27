#pragma once

#include "Entity.hpp"
#include "Bullet.hpp"

const float SOLDIER_MOVE_SPEED = 2.f;
const int SOLDIER_TURN_SPEED = 3;
const float SOLDIER_SIZE = 10.f;
const int SOLDIER_POINT_COUNT = 3;

const int SOLDIER_BULLETES_NUMBER = 10;
const int SOLDIER_SHOOT_COOLDOWN = 300;
const int SOLDIER_RELOAD_COOLDOWN = 2000;

enum class SoldierMovePower {
	FORWARD = 1,
	STOP = 0
};

class Soldier : public MoveableEntity {

protected:

	SoldierMovePower movePower = SoldierMovePower::STOP;

	int nBulletes;
	bool reloading;

	sf::Clock shootClock;
	sf::Clock reloadClock;

	void updateByDoor(Door& door);
	void updateByRoom(Room& room);

	void moveThroughDoors(doors_con_t doors);
	void moveInRooms(rooms_con_t rooms);

public:

	Soldier(sf::Color color) : MoveableEntity(SOLDIER_SIZE, SOLDIER_POINT_COUNT, color), nBulletes(SOLDIER_BULLETES_NUMBER), reloading(false) {};

	void shoot(bulletes_con_t& bulletes);

	void reload();

	void update(rooms_con_t& rooms, doors_con_t& doors);
};
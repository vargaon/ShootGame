#pragma once
#include "Entity.hpp"
#include "Map.hpp"
#include "Bullet.hpp"

const float PERSON_SIZE = 10.f;
const int PERSON_POINT_COUNT = 3;

enum class PersonMovePower {
	FORWARD,
	STOP
};

class Person: public MoveableEntity {

protected:

	PersonMovePower movePower = PersonMovePower::STOP;

	void moveInRooms(rooms_con_t& rooms, Bounds& bounds);
	void moveInDoors(doors_con_t& doors, Bounds& bounds);

public:

	Person(sf::Color color) : MoveableEntity(PERSON_SIZE, PERSON_POINT_COUNT, color) {};
	void setMovePower(PersonMovePower mp);
	void setDirectionByPosition(float x, float y);

};
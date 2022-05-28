#pragma once

#include "MoveableEntity.hpp"
#include "Map.hpp"

const float PERSON_SIZE = 10.f;
const int PERSON_POINT_COUNT = 3;

enum class PersonMovePower {
	FORWARD,
	STOP
};

class Person: public MoveableEntity {
public:

	Person(sf::Color color) : MoveableEntity(PERSON_SIZE, PERSON_POINT_COUNT, color) {};

	Room* getRoom() const;

	void setMovePower(PersonMovePower mp);
	void setDirectionByPosition(Position& p);
	void setStartPositionByRoom(Room* pRoom);

protected:

	Room* room = nullptr;
	PersonMovePower movePower = PersonMovePower::STOP;

	void move(Map& map, float speed);
	
private:

	bool inRoom(const Room& r) const;

	void moveInRoom(const Room& r);
	void moveInRooms(rooms_con_t& rooms, bool mayChangeRoom);
	void moveInDoors(const doors_con_t& doors);
};
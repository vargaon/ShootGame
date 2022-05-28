#pragma once

#include "RectangleEntity.hpp"
#include "Room.hpp"

const float GATE_SIZE = 20.f;
const sf::Color GATE_COLOR = {255,255,255,255};

class NextLevelGate : public RectangleEntity {

public:

	NextLevelGate() : RectangleEntity(GATE_SIZE, GATE_SIZE, GATE_COLOR) {};

	Room* getRoom();

	void setPositionByRoom(Room* r);
	bool tryEnter(const Bounds& b);

private:

	Room* room = nullptr;
};
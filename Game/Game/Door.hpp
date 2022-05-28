#pragma once

#include <vector>

#include "RectangleEntity.hpp"
#include "Room.hpp"

const float DOOR_SIZE = 70.f;
const sf::Color DOOR_COLOR = { 0,255,0,255 };

class Door : public RectangleEntity {

public:

	Door(bool horizontal, Position p);

	bool isHorizontal() const;

private:

	bool horizontal;
};

using doors_con_t = std::vector<Door>;

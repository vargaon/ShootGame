#pragma once

#include <iostream>
#include <vector>

#include "Bounds.hpp"
#include "Item.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;

enum class RoomPosition {
	LEFT_UP,
	RIGTH_UP,
	LEFT_BOT,
	RIGHT_BOT
};

class Room {

private:

	items_con_t items;

public:

	Bounds outerBounds;
	Bounds innerBounds;

	Room(float x, float y);

	void addItem(item_ptr_t i, RoomPosition p);
};

using rooms_con_t = std::vector<Room>;
#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "Bounds.hpp"
#include "Item.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;

enum class RoomPosition {
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOT,
	RIGHT_BOT,
	CENTRE
};

using room_position_con_t = std::map<RoomPosition, Position>;
using room_items_con_t = std::map<RoomPosition, Item>;

class Room {

private:

	room_items_con_t items;
	room_position_con_t positions;

public:

	Bounds outerBounds;
	Bounds innerBounds;

	Room(float x, float y);

	void addItem(Item i, RoomPosition rp);
	Position getRoomPosition(RoomPosition rp);
	void render(sf::RenderWindow* window);
	void update();
};

using rooms_con_t = std::vector<Room>;
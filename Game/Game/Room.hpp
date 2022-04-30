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

	room_position_con_t positions;

	void initRoomPositions();

public:

	int id = 0;

	room_items_con_t items;

	Bounds outerBounds;
	Bounds innerBounds;

	Room() {};
	Room(int id, float x, float y);

	void addItem(RoomPosition rp);

	Position getRoomPosition(RoomPosition rp);
	void render(sf::RenderWindow* window);
	void update();
};

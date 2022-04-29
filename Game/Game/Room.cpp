#include "Room.hpp"

Room::Room(float x, float y)
{
	float globalRoomSize = ROOM_SIZE + 2 * WALL_THICKNESS;
	float localRoomSize = WALL_THICKNESS + ROOM_SIZE;

	this->outerBounds = Bounds(y, y + globalRoomSize, x, x + globalRoomSize);
	this->innerBounds = Bounds(y + WALL_THICKNESS, y + localRoomSize, x + WALL_THICKNESS, x + localRoomSize);
}

void Room::addItem(item_ptr_t i, RoomPosition p)
{
	//TODO: set item position
	this->items.push_back(std::move(i));
}

#include "Room.hpp"

Room::Room(float x, float y)
{
	float globalRoomSize = ROOM_SIZE + 2 * WALL_THICKNESS;
	float localRoomSize = WALL_THICKNESS + ROOM_SIZE;

	this->outerBounds = Bounds(y, y + globalRoomSize, x, x + globalRoomSize);
	this->innerBounds = Bounds(y + WALL_THICKNESS, y + localRoomSize, x + WALL_THICKNESS, x + localRoomSize);

	this->initRoomPositions();
}

void Room::initRoomPositions()
{
	float itemPositionPadding = 20.f;

	this->positions[RoomPosition::CENTRE] = Position((this->innerBounds.right - this->innerBounds.left) / 2, (this->innerBounds.bot - this->innerBounds.top) / 2);

	this->positions[RoomPosition::LEFT_TOP] = Position(this->innerBounds.left + itemPositionPadding, this->innerBounds.top + itemPositionPadding);
	this->positions[RoomPosition::LEFT_BOT] = Position(this->innerBounds.left + itemPositionPadding, this->innerBounds.bot - itemPositionPadding);
	this->positions[RoomPosition::RIGHT_BOT] = Position(this->innerBounds.right - itemPositionPadding, this->innerBounds.bot - itemPositionPadding);
	this->positions[RoomPosition::RIGHT_TOP] = Position(this->innerBounds.right - itemPositionPadding, this->innerBounds.top + itemPositionPadding);
}

void Room::addItem(RoomPosition rp)
{
	auto ip = this->getRoomPosition(rp);

	Item i(ip.x, ip.y);

	this->items.insert({ rp , i });
}

Position Room::getRoomPosition(RoomPosition rp)
{
	auto it = this->positions.find(rp);

	if (it != this->positions.end()) {
		return it->second;
	}

	throw ("Room position was not set.");
}

void Room::render(sf::RenderWindow* window)
{
	for (auto&& i : items) {
		i.second.render(window);
	}
}

void Room::update()
{
	for (auto it = this->items.begin(); it != this->items.end();) {

		if (!it->second.isActive()) {
			it = this->items.erase(it);
		}
		else {
			it++;
		}
	}
}


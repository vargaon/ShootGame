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
	this->positions[RoomPosition::CENTRE] = Position((this->innerBounds.right - this->innerBounds.left) / 2, (this->innerBounds.bot - this->innerBounds.top) / 2);
	this->positions[RoomPosition::LEFT_TOP] = Position(this->innerBounds.left + 20, this->innerBounds.top + 20);
	this->positions[RoomPosition::LEFT_BOT] = Position(this->innerBounds.left + 20, this->innerBounds.bot - 20);
	this->positions[RoomPosition::RIGHT_BOT] = Position(this->innerBounds.right - 20, this->innerBounds.bot - 20);
	this->positions[RoomPosition::RIGHT_TOP] = Position(this->innerBounds.right - 20, this->innerBounds.top + 20);
}

void Room::addItem(ItemType it, RoomPosition rp)
{
	auto ip = this->positions[rp];
	Item i(it, ip.x, ip.y);
	this->items.insert({ rp , i });
}

Position Room::getRoomPosition(RoomPosition rp)
{
	return this->positions[rp];
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


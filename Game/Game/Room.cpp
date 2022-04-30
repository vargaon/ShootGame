#include "Room.hpp"

Room::Room(int id, float x, float y): id(id), x(x), y(y)
{
	float globalRoomSize = ROOM_SIZE + 2 * WALL_THICKNESS;
	float localRoomSize = WALL_THICKNESS + ROOM_SIZE;

	this->outerBounds = Bounds(y, y + globalRoomSize, x, x + globalRoomSize);
	this->innerBounds = Bounds(y + WALL_THICKNESS, y + localRoomSize, x + WALL_THICKNESS, x + localRoomSize);

	this->cx = this->innerBounds.left + (this->innerBounds.right - this->innerBounds.left) / 2;
	this->cy = this->innerBounds.top + (this->innerBounds.bot - this->innerBounds.top) / 2;

	this->maxX = int(this->innerBounds.right - ROOM_PADDING);
	this->minX = int(this->innerBounds.left + ROOM_PADDING);
	this->maxY = int(this->innerBounds.bot - ROOM_PADDING);
	this->minY = int(this->innerBounds.top + ROOM_PADDING);
}

void Room::addItem()
{
	auto p = this->getRandomPosition();

	Item i(p.x, p.y);
	this->items.push_back(i);
}

Position Room::getRandomPosition()
{
	int rx = minX + rand() % (maxX - minX + 1);
	int ry = minY + rand() % (maxY - minY + 1);

	return Position(float(rx), float(ry));
}

Position Room::getPosition()
{
	return Position(this->cx, this->cy);
}

void Room::render(sf::RenderWindow* window)
{
	for (auto&& i : this->items) {
		i.render(window);
	}
}

void Room::update()
{
	for (auto it = this->items.begin(); it != this->items.end();) {

		it->update();

		if (!it->isActive()) {
			it = this->items.erase(it);
		}
		else {
			it++;
		}
	}
}


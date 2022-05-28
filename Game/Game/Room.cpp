#include "Room.hpp"

Room::Room(int id, Position p): id(id)
{
	float outerRoomSize = ROOM_SIZE + 2 * WALL_THICKNESS;
	float innerRoomSize = ROOM_SIZE;
	float spawnRoomSize = innerRoomSize - ROOM_PADDING;

	this->centrePosition = { p.x + outerRoomSize / 2, p.y + outerRoomSize / 2 };

	this->outerBounds = Bounds(outerRoomSize, outerRoomSize, this->centrePosition);
	this->innerBounds = Bounds(innerRoomSize, innerRoomSize, this->centrePosition);
	this->spawnRange = Bounds(spawnRoomSize, spawnRoomSize, this->centrePosition);

	this->background.setPosition(p.x + WALL_THICKNESS, p.y + WALL_THICKNESS);
	this->background.setSize({ ROOM_SIZE, ROOM_SIZE });
	this->setRoomBackgroupColor(ROOM_BACKGROUND_COLOR);
}

void Room::createItem()
{
	this->items.push_back({ this->getRandomPosition() });
}

Position Room::getRandomPosition() const
{
	int rx = int(this->spawnRange.getLeft()) + rand() % (int(this->spawnRange.getRight()) - int(this->spawnRange.getLeft()) + 1);
	int ry = int(this->spawnRange.getTop()) + rand() % (int(this->spawnRange.getBot()) - int(this->spawnRange.getTop()) + 1);

	return { float(rx), float(ry) };
}

Position Room::getCentrePosition() const
{
	return this->centrePosition;
}

int Room::getId() const
{
	return this->id;
}

items_con_t& Room::getItems()
{
	return this->items;
}

const neighbor_rooms_con_t& Room::getNeighborhood() const
{
	return this->neighborhood;
}

const Bounds& Room::getOuterBounds() const
{
	return this->outerBounds;
}

const Bounds& Room::getInnerBounds() const
{
	return this->innerBounds;
}

void Room::setRoomBackgroupColor(sf::Color color)
{
	this->background.setFillColor(color);
}

void Room::updateItems()
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

void Room::update()
{
	this->setRoomBackgroupColor(ROOM_BACKGROUND_COLOR);
	this->updateItems();
}

void Room::clear()
{
	this->items.clear();
	this->neighborhood.clear();
}

void Room::drawBackgroundAt(sf::RenderWindow* window)
{
	window->draw(this->background);
}

void Room::drawItemsAt(sf::RenderWindow* window)
{
	for (auto&& i : this->items) {
		i.drawAt(window);
	}
}

void Room::addNeighbor(Room* room)
{
	this->neighborhood.push_back(room);
}

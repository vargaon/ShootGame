#include "Room.hpp"

Room::Room(int id, Position p): id(id)
{
	float globalRoomSize = ROOM_SIZE + 2 * WALL_THICKNESS;
	float localRoomSize = WALL_THICKNESS + ROOM_SIZE;

	this->outerBounds = Bounds(p.y, p.y + globalRoomSize, p.x, p.x + globalRoomSize);
	this->innerBounds = Bounds(p.y + WALL_THICKNESS, p.y + localRoomSize, p.x + WALL_THICKNESS, p.x + localRoomSize);

	this->centrePosition = Position(
		this->innerBounds.left + (this->innerBounds.right - this->innerBounds.left) / 2 , 
		this->innerBounds.top + (this->innerBounds.bot - this->innerBounds.top) / 2 
	);

	this->spawnRange = Bounds(
		this->innerBounds.top + ROOM_PADDING, 
		this->innerBounds.bot - ROOM_PADDING, 
		this->innerBounds.left + ROOM_PADDING, 
		this->innerBounds.right - ROOM_PADDING
	);

	//initialize room background
	this->background.setPosition(p.x + WALL_THICKNESS, p.y + WALL_THICKNESS);
	this->background.setSize({ ROOM_SIZE, ROOM_SIZE });
	this->setRoomBackgroupColor(ROOM_BACKGROUND_COLOR);
}

void Room::addItem()
{
	this->items.push_back({ this->getRandomPosition() });
}

Position Room::getRandomPosition() const
{
	int rx = int(this->spawnRange.left) + rand() % (int(this->spawnRange.right) - int(this->spawnRange.left) + 1);
	int ry = int(this->spawnRange.top) + rand() % (int(this->spawnRange.bot) - int(this->spawnRange.top) + 1);

	return { float(rx), float(ry) };
}

Position Room::getCentrePosition() const
{
	return this->centrePosition;
}

void Room::setRoomBackgroupColor(sf::Color color)
{
	this->background.setFillColor(color);
}

void Room::render(sf::RenderWindow* window)
{
	window->draw(this->background);
}

void Room::renderItems(sf::RenderWindow* window)
{
	for (auto&& i : this->items) {
		i.render(window);
	}
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


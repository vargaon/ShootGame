#include "Map.hpp"

using namespace sf;

Map::Map()
{
	this->background.setSize({ this->mapSize, this->mapSize });

	this->initWalls();
	this->initRooms();
}

void Map::update()
{
	for (auto&& r : this->rooms)
	{
		r.update();
	}
}

void Map::initWalls()
{
	float wallDistance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i <= NUM_OF_ROOM_PER_LINE; i++) {

		this->createWall(false, { i * wallDistance, 0 });
		this->createWall(true, { 0, i * wallDistance });
	}
}

void Map::initRooms()
{
	float distance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {

		for (int j = 0; j < NUM_OF_ROOM_PER_LINE; j++) {

			int id = i * NUM_OF_ROOM_PER_LINE + j;
			this->rooms[id] = Room(id, { i * distance, j * distance });
		}
	}
}

void Map::createWall(bool isHorizontal, Position p)
{
	Vector2f s;

	if (isHorizontal) {
		s = Vector2f(this->mapSize, WALL_THICKNESS);
	}
	else {
		s = Vector2f(WALL_THICKNESS, this->mapSize);
	}

	RectangleShape wall(s);

	wall.setFillColor(WALL_COLOR);
	wall.setPosition(p.x, p.y);

	this->walls.push_back(wall);
}

void Map::createDoorsByMask(bool isHorizontal, const door_mask_t& mask)
{
	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {

		for (int j = 0; j < NUM_OF_ROOM_PER_LINE - 1; j++) {

			if (mask.at(i).at(j)) {

				float x = i * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS + ((ROOM_SIZE - DOOR_SIZE) / 2);
				float y = (j + 1) * (WALL_THICKNESS + ROOM_SIZE);

				if (isHorizontal) {
					this->doors.push_back(Door(isHorizontal, Position(x, y)));
				}
				else {
					this->doors.push_back(Door(isHorizontal, Position(y, x)));
				}
			}
		}
	}
}

void Map::setup(const MapSetting& s)
{
	this->background.setFillColor(s.backgroundColor);

	this->createDoorsByMask(false, s.verticalDoorMask);
	this->createDoorsByMask(true, s.horizontalDoorMask);

	for (auto&& r : this->rooms) {
		r.items.clear();
	}

	this->itemsCreated = 0;
}

void Map::createItem()
{
	auto r = this->getRandomRoom();
	r->addItem();

	++this->itemsCreated;
}

Room* Map::getRoom(int id)
{
	return &this->rooms.at(id);
}

Room* Map::getRandomRoom()
{
	int roomID = rand() % this->roomNum;
	return this->getRoom(roomID);
}

Room* Map::getRandomRoom(int exclude)
{
	int roomID = rand() % this->roomNum;

	if (roomID == exclude) {
		roomID = (exclude + 1) % this->roomNum;
	}

	return this->getRoom(roomID);
}

int Map::getTotalItems() const
{
	return this->itemsCreated;
}

void Map::render(sf::RenderWindow* window)
{
	window->draw(this->background);

	for (auto&& w : this->walls) {
		window->draw(w);
	}

	for (auto&& d : this->doors) {
		d.render(window);
	}

	for (auto&& r : this->rooms) {
		r.render(window);
	}
}

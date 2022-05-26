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
	for (auto&& roomRow : this->rooms)
	{
		for (auto&& r : roomRow) {
			r.update();
		}
	}
}

void Map::initWalls()
{
	float wallDistance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i <= NUM_OF_ROOM_PER_LINE; i++) {

		walls[i] = this->createWall(false, { i * wallDistance, 0 });
		walls[NUM_OF_ROOM_PER_LINE + i] = this->createWall(true, { 0, i * wallDistance });
	}
}

RectangleShape Map::createWall(bool isHorizontal, Position p)
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

	return wall;
}

void Map::initRooms()
{
	float distance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {

		for (int j = 0; j < NUM_OF_ROOM_PER_LINE; j++) {

			this->rooms[i][j] = Room(i * NUM_OF_ROOM_PER_LINE + j, { i * distance, j * distance });
		}
	}
}

void Map::setupRoomNeighbors(const door_mask_t& hMask, const door_mask_t& vMask)
{
	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {
		for (int j = 0; j < NUM_OF_ROOM_PER_LINE; j++) {

			int top = j - 1;

			if (top >= 0) {

				if (hMask[i][top]) {
					this->rooms[i][j].neighbors.push_back(&this->rooms[i][top]);
				}
			}

			int bot = j + 1;

			if (bot < NUM_OF_ROOM_PER_LINE) {

				if (hMask[i][j]) {
					this->rooms[i][j].neighbors.push_back(&this->rooms[i][bot]);
				}
			}

			int left = i - 1;

			if (left >= 0) {

				if (vMask[j][left]) {
					this->rooms[i][j].neighbors.push_back(&this->rooms[left][j]);
				}
			}

			int right = i + 1;

			if (right < NUM_OF_ROOM_PER_LINE) {

				if (vMask[j][i]) {
					this->rooms[i][j].neighbors.push_back(&this->rooms[right][j]);
				}
			}
		}
	}
}

void Map::setupDoors(bool isHorizontal, const door_mask_t& mask)
{
	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {

		for (int j = 0; j < NUM_OF_ROOM_PER_LINE - 1; j++) {

			if (mask[i][j]) {

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

	this->setupDoors(false, s.verticalDoorMask);
	this->setupDoors(true, s.horizontalDoorMask);

	for (auto&& roomRow : this->rooms) {

		for (auto&& r : roomRow) {
			r.items.clear();
			r.neighbors.clear();
		}
	}

	this->setupRoomNeighbors(s.horizontalDoorMask, s.verticalDoorMask);

	

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
	int row = id / NUM_OF_ROOM_PER_LINE;

	int col = id % NUM_OF_ROOM_PER_LINE;

	return &this->rooms.at(row).at(col);
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

	for (auto&& roomRow : this->rooms) {

		for (auto&& r : roomRow) {
			r.render(window);
		}
	}
}

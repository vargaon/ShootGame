#include "Map.hpp"

using namespace sf;

Map::Map()
{
	this->initWalls();
	this->initRooms();
}

void Map::initWalls()
{
	float wallDistance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i <= NUM_OF_ROOM_PER_LINE; i++) {

		walls[i] = this->createWall(false, { i * wallDistance, 0 });
		walls[NUM_OF_ROOM_PER_LINE + 1 + i] = this->createWall(true, { 0, i * wallDistance });
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
					this->rooms[i][j].addNeighbor(&this->rooms[i][top]);
				}
			}

			int bot = j + 1;

			if (bot < NUM_OF_ROOM_PER_LINE) {

				if (hMask[i][j]) {
					this->rooms[i][j].addNeighbor(&this->rooms[i][bot]);
				}
			}

			int left = i - 1;

			if (left >= 0) {

				if (vMask[j][left]) {
					this->rooms[i][j].addNeighbor(&this->rooms[left][j]);
				}
			}

			int right = i + 1;

			if (right < NUM_OF_ROOM_PER_LINE) {

				if (vMask[j][i]) {
					this->rooms[i][j].addNeighbor(&this->rooms[right][j]);
				}
			}

			this->rooms[i][j].addNeighbor(&this->rooms[i][j]);
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

void Map::setup(const MapSetting& mapSetting)
{
	this->doors.clear();

	this->setupDoors(false, mapSetting.verticalDoorMask);
	this->setupDoors(true, mapSetting.horizontalDoorMask);

	for (auto&& roomRow : this->rooms) {

		for (auto&& r : roomRow) {
			r.clear();
		}
	}

	this->setupRoomNeighbors(mapSetting.horizontalDoorMask, mapSetting.verticalDoorMask);
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

void Map::createCoin()
{
	auto r = this->getRandomRoom();
	r->createCoin();
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

Room* Map::getRandomRoom(const std::vector<Room*>& exclude)
{
	std::vector<Room*> temp;

	for (auto&& roomRow : this->rooms) {
		for (auto&& r : roomRow) {
			if (std::find(exclude.begin(), exclude.end(), &r) == exclude.end()) {
				temp.push_back(&r);
			}
		}
	}

	int randomPos = rand() % temp.size();

	return temp[randomPos];
}

void Map::drawAt(sf::RenderWindow* window, Room* playerRoom)
{
	for (auto&& w : this->walls) {
		window->draw(w);
	}

	for (auto&& d : this->doors) {
		d.drawAt(window);
	}

	for (auto&& roomRow : this->rooms) {

		for (auto&& r : roomRow) {
			r.drawBackgroundAt(window);
		}
	}

	for (auto&& r : playerRoom->getNeighborhood()) {
		r->drawItemsAt(window);
	}
}

#include "Map.hpp"

using namespace sf;

Map::Map()
{
	this->initWalls();
	this->initDoors();
	this->initRooms();
}

void Map::initWalls()
{
	float wallDistance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i <= NUM_OF_ROOM_PER_LINE; i++) {

		this->createWall(false, i * wallDistance, 0);
		this->createWall(true, 0, i * wallDistance);
	}
}

void Map::initRooms()
{
	float distance = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {

		for (int j = 0; j < NUM_OF_ROOM_PER_LINE; j++) {

			this->rooms.push_back(Room(i * distance, j * distance));
		}
	}
}

void Map::initDoors()
{
	//TODO: differen masks

	door_mask_t doorsMask = { {
		{true, true, true, true},
		{false, true, true, false},
		{true, true, true, true},
		{false, true, true, false},
		{true, true, true, true}
	} };

	this->createDoorsByMask(false, doorsMask);
	this->createDoorsByMask(true, doorsMask);
}

void Map::createWall(bool isHorizontal, float x, float y)
{
	Vector2f s;

	if (isHorizontal) {
		s = Vector2f(this->mapSize, WALL_THICKNESS);
	}
	else {
		s = Vector2f(WALL_THICKNESS, this->mapSize);
	}

	RectangleShape wall(s);

	wall.setFillColor(Color::Black);
	wall.setPosition(x, y);

	this->walls.push_back(wall);
}

void Map::createDoorsByMask(bool isHorizontal, door_mask_t& mask)
{
	for (int i = 0; i < NUM_OF_ROOM_PER_LINE; i++) {

		for (int j = 0; j < NUM_OF_ROOM_PER_LINE - 1; j++) {

			if (mask.at(i).at(j)) {

				float x = i * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS + ((ROOM_SIZE - DOOR_SIZE) / 2);
				float y = (j + 1) * (WALL_THICKNESS + ROOM_SIZE);

				if (isHorizontal) {
					this->doors.push_back(Door(isHorizontal, x, y));
				}
				else {
					this->doors.push_back(Door(isHorizontal, y, x));
				}
			}
		}
	}
}

void Map::render(sf::RenderWindow* window)
{
	for (auto&& w : this->walls) {
		window->draw(w);
	}

	for (auto&& d : this->doors) {
		d.render(window);
	}
}
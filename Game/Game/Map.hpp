#pragma once
#include <SFML/Graphics.hpp> 
#include <array>
#include <vector>
#include "Room.hpp"
#include "Door.hpp"

const int NUM_OF_ROOM_PER_LINE = 5;

using rooms_con_t = std::array<Room, NUM_OF_ROOM_PER_LINE * NUM_OF_ROOM_PER_LINE>;
using door_mask_t = std::array<std::array<bool, NUM_OF_ROOM_PER_LINE - 1>, NUM_OF_ROOM_PER_LINE>;

class Map {
private:

	float mapSize = NUM_OF_ROOM_PER_LINE * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS;

	void initWalls();
	void initRooms();
	void initDoors();
	void initItems();

	void createWall(bool isHorizontal, float x, float y);
	void createDoorsByMask(bool isHorizontal, door_mask_t& mask);

	std::vector<sf::RectangleShape> walls;

public:

	rooms_con_t rooms;
	doors_con_t doors;

	Map();

	void render(sf::RenderWindow* window);
};
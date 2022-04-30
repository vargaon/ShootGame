#pragma once
#include <SFML/Graphics.hpp> 
#include <array>
#include <vector>
#include <cstdlib>
#include "Room.hpp"
#include "Door.hpp"

const int NUM_OF_ROOM_PER_LINE = 5;
const int ITEM_SPAW_COOLDOWN = 2500;

using rooms_con_t = std::array<Room, NUM_OF_ROOM_PER_LINE * NUM_OF_ROOM_PER_LINE>;
using door_mask_t = std::array<std::array<bool, NUM_OF_ROOM_PER_LINE - 1>, NUM_OF_ROOM_PER_LINE>;

class Map {
private:

	float mapSize = NUM_OF_ROOM_PER_LINE * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS;

	int itemsCreated = 0;

	sf::Clock itemSpawnClock;

	void initWalls();
	void initRooms();
	void initDoors();

	void createWall(bool isHorizontal, Position p);
	void createDoorsByMask(bool isHorizontal, door_mask_t& mask);

	void createItem();

	std::vector<sf::RectangleShape> walls;

public:

	rooms_con_t rooms;
	doors_con_t doors;

	Map();

	Room* getRoom(int id);
	Room* getRandomRoom();

	int getTotalItems();

	void update();
	void render(sf::RenderWindow* window);
};
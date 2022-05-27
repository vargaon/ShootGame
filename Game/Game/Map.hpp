#pragma once
#include <SFML/Graphics.hpp> 
#include <array>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "MapSetting.hpp"

const sf::Color WALL_COLOR = { 0, 0, 0, 255 };

using rooms_con_t = std::array< std::array<Room, NUM_OF_ROOM_PER_LINE>, NUM_OF_ROOM_PER_LINE>;

class Map {

public:

	rooms_con_t rooms;
	doors_con_t doors;

	Map();

	Room* getRoom(int id);
	Room* getRandomRoom();
	Room* getRandomRoom(const std::vector<Room*>& exclude);

	int getTotalItems() const;
	void createItem();

	void setup(const MapSetting & s);

	void update();
	void render(sf::RenderWindow* window, const Room* playerRoom);

private:

	float mapSize = NUM_OF_ROOM_PER_LINE * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS;
	int roomNum = NUM_OF_ROOM_PER_LINE * NUM_OF_ROOM_PER_LINE;

	std::array<sf::RectangleShape, (NUM_OF_ROOM_PER_LINE * 2) + 2> walls;

	int itemsCreated = 0;

	void initWalls();
	sf::RectangleShape createWall(bool isHorizontal, Position p);

	void initRooms();

	void setupRoomNeighbors(const door_mask_t& hMask, const door_mask_t& vMask);
	void setupDoors(bool isHorizontal, const door_mask_t& mask);
};
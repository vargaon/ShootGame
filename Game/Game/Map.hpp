#pragma once
#include <SFML/Graphics.hpp> 
#include <array>
#include <vector>
#include <cstdlib>
#include "MapSetting.hpp"

const sf::Color WALL_COLOR = { 0, 0, 0, 255 };

using rooms_con_t = std::array<Room, NUM_OF_ROOM_PER_LINE* NUM_OF_ROOM_PER_LINE>;

class Map {

public:

	rooms_con_t rooms;
	doors_con_t doors;

	Map();

	Room* getRoom(int id);
	Room* getRandomRoom();

	int getTotalItems() const;
	void createItem();

	void setup(const MapSetting & s);

	void update();
	void render(sf::RenderWindow* window);

private:

	float mapSize = NUM_OF_ROOM_PER_LINE * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS;

	sf::RectangleShape background;

	int itemsCreated = 0;

	void initWalls();
	void initRooms();

	void createWall(bool isHorizontal, Position p);
	void createDoorsByMask(bool isHorizontal, const door_mask_t& mask);

	std::vector<sf::RectangleShape> walls;
};
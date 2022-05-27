#pragma once

#include <iostream>
#include <vector>
#include "Utils.hpp"
#include "Item.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;
const int ROOM_PADDING = 15;
const sf::Color ROOM_BACKGROUND_COLOR = { 140,140,140,255 };

class Room;

using neighbor_rooms_con_t = std::vector<Room*>;

class Room {

public:

	int id = 0;

	items_con_t items;
	neighbor_rooms_con_t neighborhood;

	Bounds outerBounds;
	Bounds innerBounds;

	Room() {};
	Room(int id, Position p);

	void addItem();
	Position getRandomPosition() const;
	Position getCentrePosition() const;

	void setRoomBackgroupColor(sf::Color color);

	void renderBackground(sf::RenderWindow* window);
	void renderItems(sf::RenderWindow* window);
	void update();

private:

	Position centrePosition;
	Bounds spawnRange;

	sf::RectangleShape background;

	void updateItems();
};

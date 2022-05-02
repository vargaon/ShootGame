#pragma once

#include <iostream>
#include <vector>
#include "Utils.hpp"
#include "Item.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;
const int ROOM_PADDING = 10;

class Room {

public:

	int id = 0;

	items_con_t items;

	Bounds outerBounds;
	Bounds innerBounds;

	Room() {};
	Room(int id, Position p);

	void addItem();
	Position getRandomPosition() const;
	Position getCentrePosition() const;

	void render(sf::RenderWindow* window);
	void update();

private:

	Position centrePosition;
	Bounds spawnRange;

	void updateItems();
};

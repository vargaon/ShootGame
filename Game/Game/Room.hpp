#pragma once

#include <iostream>
#include <vector>
#include "Utils.hpp"
#include "Item.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;
const int ROOM_PADDING = 10;

class Room {

private:
	Position p;

	float cx = 0.f;
	float cy = 0.f;

	Bounds spawnRange;

	int maxX = 0;
	int minX = 0;

	int maxY = 0;
	int minY = 0;

public:

	int id = 0;

	items_con_t items;

	Bounds outerBounds;
	Bounds innerBounds;

	Room() {};
	Room(int id, Position p);

	void addItem();
	Position getRandomPosition();
	Position getCentrePosition();

	void render(sf::RenderWindow* window);
	void update();
};

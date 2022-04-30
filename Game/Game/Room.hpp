#pragma once

#include <iostream>
#include <vector>
#include "Bounds.hpp"
#include "Item.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;
const int ROOM_PADDING = 10;

class Room {

private:
	float x = 0.f;
	float y = 0.f;

	float cx = 0.f;
	float cy = 0.f;

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
	Room(int id, float x, float y);

	void addItem();
	Position getRandomPosition();
	Position getPosition();

	void render(sf::RenderWindow* window);
	void update();
};

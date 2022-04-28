#pragma once

#include <SFML/Graphics.hpp> 
#include <iostream>
#include <vector>
#include "Item.hpp"

enum class RoomPosition {
	LEFT_UP,
	RIGTH_UP,
	LEFT_BOT,
	RIGHT_BOT
};

class Room {

private:

	float top;
	float left;
	float bot;
	float right;
	float wallThickness;
	sf::FloatRect localBounds;

	items_con_t items;

public:

	Room(float top, float left, float bot, float right, float wallThickness);

	void addItem(item_ptr_t i, RoomPosition p);

	bool inRoom(sf::FloatRect rect);
	bool inLocalBounds(sf::FloatRect rect);

	sf::FloatRect getLocalBounds();

	void print();
};

using rooms_con_t = std::vector<Room>;
#pragma once

#include <SFML/Graphics.hpp> 
#include <iostream>
#include <vector>

class Room {

private:

	float top;
	float left;
	float bot;
	float right;

	float wallThickness;

	sf::FloatRect localBounds;

public:

	Room(float top, float left, float bot, float right, float wallThickness);

	bool inRoom(sf::FloatRect rect);
	bool inLocalBounds(sf::FloatRect rect);

	sf::FloatRect getLocalBounds();

	void print();
};

using rooms_con_t = std::vector<Room>;
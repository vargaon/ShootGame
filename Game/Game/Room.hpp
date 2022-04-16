#pragma once

#include <SFML/Graphics.hpp> 
#include <iostream>

class Room {

public:

	float top;
	float left;
	float bot;
	float right;

	Room(float top, float left, float bot, float right) : top(top), left(left), bot(bot), right(right) {};
	bool inRoom(sf::Vector2f position, float size);

	void print();
};
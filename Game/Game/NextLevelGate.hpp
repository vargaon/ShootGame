#pragma once

#include <SFML/Graphics.hpp> 
#include "Room.hpp"
#include "Utils.hpp"

const float GATE_SIZE = 20.f;
const sf::Color GATE_COLOR = {255,255,255,255};

class NextLevelGate {
public:

	Room* room = nullptr;

	NextLevelGate();
	void setPosition(Room* room);
	bool enteredGate(const Bounds& b);
	void render(sf::RenderWindow* window);
private:
	Bounds bounds;
	sf::RectangleShape entity;
};
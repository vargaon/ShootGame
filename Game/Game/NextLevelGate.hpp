#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.hpp"

const float GATE_SIZE = 20.f;
const sf::Color GATE_COLOR = {255,255,255,255};

class NextLevelGate {
public:
	NextLevelGate();
	void setPosition(Position p);
	bool enteredGate(const Bounds& b);
	void render(sf::RenderWindow* window);
private:
	Bounds bounds;
	sf::RectangleShape entity;
};
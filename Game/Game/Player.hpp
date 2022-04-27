#pragma once
#include "Soldier.hpp"

class Player: public Soldier {

public:

	Player(): Soldier(sf::Color::Red) {};

	void changeDirection(sf::Vector2i mousePos);
	void move();
	void stop();
};

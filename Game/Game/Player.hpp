#pragma once
#include "Soldier.hpp"

class Player: public Soldier {

public:

	Player(): Soldier(sf::Color::Red) {};

	void turnLeft();
	void turnRight();
	void goForward();
	void goBack();
	void stop();
};

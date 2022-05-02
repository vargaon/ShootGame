#pragma once
#include "Person.hpp"
#include <vector>

const float ZOMBIE_MOVE_SPEED = 1.f;
const sf::Color ZOMBIE_COLOR = { 255, 0, 0, 255 };

class Zombie : public Person {

public:

	Zombie() : Person(ZOMBIE_COLOR) {};
	void update(Map& m);
	bool isAlive() const;
	void die();

private:

	bool alive = true;

};

using zombies_con_t = std::vector<Zombie>;
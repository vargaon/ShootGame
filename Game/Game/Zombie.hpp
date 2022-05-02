#pragma once
#include "Person.hpp"
#include <vector>

const float ZOMBIE_MOVE_SPEED = 1.f;

class Zombie : public Person {
private:

	bool alive = true;

public:

	Zombie() : Person(sf::Color::Red) {};
	void update(Map& m);
	bool isAlive();
	void die();
};

using zombies_con_t = std::vector<Zombie>;
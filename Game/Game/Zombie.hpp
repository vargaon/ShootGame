#pragma once
#include "Person.hpp"
#include "Player.hpp"

const float ZOMBIE_MOVE_SPEED = 2.2f;

class Zombie : public Person {
private:

	bool alive = true;
	void checkForBulletes(bulletes_con_t& bulletes);

public:

	Zombie() : Person(sf::Color::Blue) {};
	void update(Map& m, Player& p, bulletes_con_t& bulletes);
	bool isAlive();
};

using zombies_con_t = std::vector<Zombie>;
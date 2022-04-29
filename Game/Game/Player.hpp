#pragma once
#include "Person.hpp"

const int PLAYER_LIVES = 3;
const float PLAYER_MOVE_SPEED = 2.f;
const int PLAYER_BULLETES_NUMBER = 10;
const int PLAYER_SHOOT_COOLDOWN = 100;
const int PLAYER_RELOAD_COOLDOWN = 2000;

class Player: public Person {

private:

	int lives = PLAYER_LIVES;
	int nBulletes = PLAYER_BULLETES_NUMBER;
	bool reloading = false;

	sf::Clock shootClock;
	sf::Clock reloadClock;

public:

	Player(): Person(sf::Color::Blue) {};
	
	Bullet shoot();
	void reload();

	bool canShoot();
	bool isReloading();
	int getBulletesNumber();
	Position getPosition();
	int getLives();
	void bite();

	void update(Map& m);
};

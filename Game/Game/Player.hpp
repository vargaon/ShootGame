#pragma once
#include "Person.hpp"

const float PLAYER_MOVE_SPEED = 2.f;
const int PLAYER_BULLETES_NUMBER = 10;
const int PLAYER_SHOOT_COOLDOWN = 100;
const int PLAYER_RELOAD_COOLDOWN = 2000;

class PlayerPosition {
public:
	float x = 0.f;
	float y = 0.f;
	PlayerPosition(float x, float y) : x(x), y(y) {};
};

class Player: public Person {

private:

	int nBulletes = PLAYER_BULLETES_NUMBER;
	bool reloading = false;

	sf::Clock shootClock;
	sf::Clock reloadClock;

public:

	Player(): Person(sf::Color::Red) {};
	
	Bullet shoot();
	void reload();

	bool canShoot();
	bool isReloading();
	int getBulletesNumber();
	PlayerPosition getPosition();

	void update(Map& m);
};

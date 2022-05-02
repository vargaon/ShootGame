#pragma once
#include "Person.hpp"
#include <iostream>

const int PLAYER_LIVES = 3;
const float PLAYER_MOVE_SPEED = 2.f;
const int PLAYER_BULLETES_NUMBER = 10;
const int PLAYER_SHOOT_COOLDOWN = 100;
const int PLAYER_RELOAD_COOLDOWN = 2000;

class Player: public Person {

public:

	Player() : Person(sf::Color::Blue) {};

	Bullet shoot();
	void reload();

	bool canShoot();
	bool isReloading();

	int getBulletesInStack();
	int getCollectedItems();
	int getLives();

	void hurt();
	void update(Map& m);

	void setup(Room* room);

private:

	int lives = PLAYER_LIVES;
	int bulletesInStack = PLAYER_BULLETES_NUMBER;
	int collectedItems = 0;
	bool reloading = false;

	sf::Clock shootClock;
	sf::Clock reloadClock;

	void checkForCollectedItems();

};

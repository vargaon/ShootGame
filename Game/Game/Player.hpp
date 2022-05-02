#pragma once
#include "Person.hpp"
#include "Zombie.hpp"
#include <iostream>

const int PLAYER_LIVES = 3;
const float PLAYER_MOVE_SPEED = 2.f;
const int PLAYER_STACK_CAPACITY = 10;
const int PLAYER_SHOOT_COOLDOWN = 100;
const int PLAYER_RELOAD_COOLDOWN = 2000;

const sf::Color PLAYER_COLOR = { 0, 0, 255, 255 };

class Player: public Person {

public:

	Player() : Person(PLAYER_COLOR) {};

	void shoot();
	void reload();

	bool canShoot();
	bool isReloading();

	int getBulletesInStack();
	int getCollectedItems();
	int getKilledZombies();
	int getLives();

	void update(Map& m, zombies_con_t& zombies);
	void render(sf::RenderWindow* window);

	void setup(Room* room);

private:

	int lives = PLAYER_LIVES;
	int bulletesInStack = PLAYER_STACK_CAPACITY;
	int collectedItems = 0;
	int killedZombies = 0;
	bool reloading = false;

	sf::Clock shootClock;
	sf::Clock reloadClock;

	bulletes_con_t bullets;

	void checkForCollectedItems();
	void checkForZombies(zombies_con_t& zombies);
	void updateBulletes(Map& m, zombies_con_t& zombies);
};

#pragma once

#include <iostream>

#include "Person.hpp"
#include "Bullet.hpp"
#include "Zombie.hpp"

const int PLAYER_LIVES = 3;
const float PLAYER_MOVE_SPEED = 2.f;
const int PLAYER_STACK_CAPACITY = 10;
const int PLAYER_SHOOT_COOLDOWN = 100;
const int PLAYER_RELOAD_COOLDOWN = 2000;

const sf::Color PLAYER_COLOR = { 0, 0, 255, 255 };
const sf::Color STANDING_ROOM_BACKGROUND_COLOR = { 165,165,165,255 };

class Player: public Person {

public:

	Player() : Person(PLAYER_COLOR) {};

	bool canShoot();
	bool isReloading();
	int getBulletesInStack();
	int getTotalCoins();
	int getLevelCoins();
	int getKilledZombies();
	int getLives();

	void init();
	void setup(Room* startRoom);

	void shoot();
	void reload();
	void update(Map& map, zombies_con_t& zombies);
	void drawAt(sf::RenderWindow* window);

private:

	int lives = PLAYER_LIVES;
	int bulletesInStack = PLAYER_STACK_CAPACITY;
	int totalCoins = 0;
	int levelCoins = 0;
	int killedZombies = 0;
	bool reloading = false;

	sf::Clock shootClock;
	sf::Clock reloadClock;

	bulletes_con_t bullets;

	void collectCoins();
	void observeZombies(zombies_con_t& zombies);
	void updateBulletes(Map& m, zombies_con_t& zombies);
};

#pragma once
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Map.hpp"

const float PLAYER_MOVE_SPEED = 2.f;
const int PLAYER_TURN_SPEED = 3;
const float PLAYER_SIZE = 10.f;
const int PLAYER_POINT_COUNT = 3;

const int PLAYER_BULLETES_NUMBER = 10;
const int PLAYER_SHOOT_COOLDOWN = 100;
const int PLAYER_RELOAD_COOLDOWN = 2000;

enum class PlayerMovePower {
	FORWARD,
	STOP
};

class Player: public MoveableEntity {

private:

	int nBulletes = PLAYER_BULLETES_NUMBER;
	bool reloading = false;

	PlayerMovePower movePower = PlayerMovePower::FORWARD;

	sf::Clock shootClock;
	sf::Clock reloadClock;

	void moveInRooms(rooms_con_t& rooms);
	void moveInDoors(doors_con_t& doors);

public:

	Player(): MoveableEntity(PLAYER_SIZE, PLAYER_POINT_COUNT, sf::Color::Red) {};
	
	void setMovePower(PlayerMovePower mp);
	Bullet shoot();
	void reload();
	void setDirectionByMousePosition(float x, float y);
	bool canShoot();
	bool isReloading();
	int getBulletesNumber();
	void update(Map& m);
};

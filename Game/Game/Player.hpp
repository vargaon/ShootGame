#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Door.hpp"
#include "Room.hpp"
#include <vector>

const float PLAYER_MOVE_SPEED = 1.5;
const int PLAYER_TURN_SPEED = 5;

const float PLAYER_SIZE = 10.f;
const int PLAYER_POINT_COUNT = 3;

enum class PlayerMove {
	FORWARD = 1,
	BACKWARD = -1,
	STOP = 0
};

class Player: public MoveableEntity {

private:

	PlayerMove move = PlayerMove::STOP;
	sf::Clock clock;

	bool lastInDoor = false;

	void updateByDoor(Door& door);
	void updateByRoom(Room& room);

	bool movementThroughDoor(doors_con_t doors);
	void movementInRoom(rooms_con_t rooms);

public:

	Player() {};
	Player(sf::Vector2f position);

	void turnLeft();
	void turnRight();
	void goForward();
	void goBack();
	void stop();
	void shoot(std::vector<Bullet>& bulletes);

	void update(rooms_con_t& rooms, doors_con_t& doors);
	void render(sf::RenderWindow& window);
};

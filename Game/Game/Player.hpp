#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Door.hpp"
#include "Room.hpp"
#include <vector>

const float PLAYER_MOVE_SPEED = 1.f;
const int PLAYER_TURN_SPEED = 3;
const float PLAYER_SIZE = 10.f;
const int PLAYER_POINT_COUNT = 3;
const int PLAYER_SHOOT_COOLDOWN = 50;

enum class PlayerMove {
	FORWARD = 1,
	BACKWARD = -1,
	STOP = 0
};

class Player: public MoveableEntity {

private:

	PlayerMove move = PlayerMove::STOP;
	sf::Clock clock;

	void updateByDoor(Door& door);
	void updateByRoom(Room& room);

	void moveThroughDoors(doors_con_t doors) override;
	void moveInRooms(rooms_con_t rooms) override;

public:

	Player() {};
	Player(sf::Vector2f position);

	void turnLeft();
	void turnRight();
	void goForward();
	void goBack();
	void stop();
	void shoot(std::vector<Bullet>& bulletes);

	void update(rooms_con_t& rooms, doors_con_t& doors) override;
};

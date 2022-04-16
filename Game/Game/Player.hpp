#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Door.hpp"
#include "Room.hpp"
#include <vector>

const int PLAYER_MOVE_SPEED = 2;
const int PLAYER_TURN_SPEED = 5;

enum PlayerMove {
	FOREWARD = 1,
	BACKWARD = -1,
	STOP = 0
};

class Player: public Entity {

private:

	int move = 0;
	sf::Clock clock;

public:

	bool inDoor = false;

	Player() {};
	Player(float size, sf::Vector2f position);

	void TurnLeft();
	void TurnRight();
	void MoveForeward();
	void MoveBack();
	void Stop();

	void Shoot(std::vector<Bullet>& bulletes);
	void updateByRoom(Room& room);
	void updateByDoor(Door& door);
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();

	virtual void Update();
	virtual void Render(sf::RenderWindow& window);
};

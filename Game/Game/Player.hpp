#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
#include <vector>

class Player: public Entity {

private:

	float dx, dy;
	int move, angle;
	sf::Clock clock;

public:
	Player();

	void TurnLeft();
	void TurnRight();
	void MoveForeward();
	void MoveBack();
	void Stop();

	void Shoot(std::vector<Bullet>& bulletes);

	virtual void Update(sf::Vector2u winSize);
	virtual void Render(sf::RenderWindow& window);
};

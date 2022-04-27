#include "Player.hpp"
#include <iostream>

using namespace sf;
 

void Player::move()
{
	this->movePower = SoldierMovePower::FORWARD;
}

void Player::stop()
{
	this->movePower = SoldierMovePower::STOP;
}

int Player::getBulletesNumber()
{
	return this->nBulletes;
}

void Player::changeDirection(sf::Vector2i mousePos)
{
	this->direction = atan2(mousePos.y - this->y, mousePos.x - this->x) * 180 / PI;
}

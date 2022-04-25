#include "Player.hpp"
#include <iostream>

using namespace sf;

void Player::turnLeft()
{
	direction -= SOLDIER_TURN_SPEED;
}

void Player::turnRight()
{
	direction += SOLDIER_TURN_SPEED;
}

void Player::goForward()
{
	this->move = SoldierMove::FORWARD;
}

void Player::goBack()
{
	this->move = SoldierMove::BACKWARD;
}

void Player::stop()
{
	this->move = SoldierMove::STOP;
}

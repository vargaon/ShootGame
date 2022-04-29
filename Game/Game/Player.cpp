#include "Player.hpp"
#include <iostream>

using namespace sf;

Bullet Player::shoot()
{
	this->shootClock.restart();

	Bullet b;

	b.setPosition(this->x, this->y);
	b.setDirection(this->getDirection());

	--this->nBulletes;

	if (this->nBulletes <= 0) {
		this->reload();
	}

	return b;
}

int Player::getBulletesNumber()
{
	return this->nBulletes;
}

PlayerPosition Player::getPosition()
{
	return PlayerPosition(this->x, this->y);
}

void Player::update(Map& m)
{
	if (this->reloading && this->reloadClock.getElapsedTime().asMilliseconds() > PLAYER_RELOAD_COOLDOWN) {
		this->reloading = false;
		this->nBulletes = PLAYER_BULLETES_NUMBER;
	}

	if (this->movePower == PersonMovePower::FORWARD) {

		this->x += this->dx * PLAYER_MOVE_SPEED;
		this->y += this->dy * PLAYER_MOVE_SPEED;
	
		this->moveInDoors(m.doors);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms);
		}
	}

	this->entity.setPosition(this->x, this->y);
	this->entity.setRotation(this->getDirection() + 90.f);
}

bool Player::canShoot()
{
	return (!this->reloading && this->nBulletes > 0 && this->shootClock.getElapsedTime().asMilliseconds() > PLAYER_SHOOT_COOLDOWN);
}

void Player::reload()
{
	this->reloading = true;
	this->reloadClock.restart();
}

bool Player::isReloading()
{
	return this->reloading;
}


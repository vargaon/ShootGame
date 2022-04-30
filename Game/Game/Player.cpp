#include "Player.hpp"
#include <iostream>

using namespace sf;

Bullet Player::shoot()
{
	this->shootClock.restart();

	Bullet b;

	b.setStartPosition(this->x, this->y);
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

Position Player::getPosition()
{
	return Position(this->x, this->y);
}

int Player::getLives()
{
	return this->lives;
}

void Player::bite()
{
	--this->lives;
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

		auto bounds = this->getBounds();
	
		this->moveInDoors(m.doors, bounds);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms, bounds);
		}
	}

	this->setPosition(this->x, this->y);
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


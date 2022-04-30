#include "Player.hpp"

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

int Player::getItemsNumber()
{
	return this->nItems;
}

Position Player::getPosition()
{
	return Position(this->x, this->y);
}

int Player::getLives()
{
	return this->lives;
}

void Player::hurt()
{
	--this->lives;
}

void Player::checkForCollectedItems()
{
	for (auto&& i : this->room->items) {
		if (this->bounds.inCollisionWith(i.bounds)) {
			i.collect();
			++this->nItems;
		}
	}
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

		this->bounds = this->getBounds();
	
		this->moveInDoors(m.doors);

		if (!this->inDoor) {
			this->moveInRooms(m.rooms);
			this->checkForCollectedItems();
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
	if (this->reloading) return;

	this->reloading = true;
	this->reloadClock.restart();
}

bool Player::isReloading()
{
	return this->reloading;
}


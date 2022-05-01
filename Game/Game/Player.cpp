#include "Player.hpp"

using namespace sf;

Bullet Player::shoot()
{
	this->shootClock.restart();

	Bullet b;

	auto p = this->getPosition();

	b.setStartPosition(p);
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

		auto ib = i.getBounds();

		if (this->bounds.inCollisionWith(ib)) {
			i.collect();
			++this->nItems;
			std::cout << "Item collected" << std::endl;
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

		Position p(this->x, this->y);
		this->setPosition(p);
	
		this->moveInDoors(m.doors);

		if (!this->inDoor) {

			this->moveInRooms(m.rooms);
			this->checkForCollectedItems();
		}
	}
}

void Player::setup(Room* room)
{
	this->lives = PLAYER_LIVES;
	this->nBulletes = PLAYER_BULLETES_NUMBER;
	this->nItems = 0;

	this->setStartPositionByRoom(room);

	this->reloadClock.restart();
	this->shootClock.restart();
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


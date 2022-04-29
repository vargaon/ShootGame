#include "Player.hpp"
#include <iostream>

using namespace sf;

void Player::moveInRooms(rooms_con_t& rooms)
{
	auto bounds = this->getBounds();

	for (auto&& r : rooms) {
		auto ob = r.outerBounds;

		if (bounds.isIn(ob)) {
			auto ib = r.innerBounds;

			if (!bounds.isIn(ib)) {

				if (bounds.left < ib.left) {
					this->x = ib.left + this->size;
				}

				if (bounds.right > ib.right) {
					this->x = ib.right - this->size;
				}

				if (bounds.top < ib.top) {
					this->y = ib.top + this->size;
				}

				if (bounds.bot > ib.bot) {
					this->y = ib.bot - this->size;
				}
			}

			break;
		}
	}
}

void Player::moveInDoors(doors_con_t& doors)
{
	auto bounds = this->getBounds();

	for (auto&& d : doors) {

		auto db = d.bounds;

		if (bounds.inCollisionWith(db)) {

			if (this->inDoor) {

				if (!bounds.inRange(d.isHorizontal(), db)) {

					if (d.isHorizontal()) {

						if (bounds.left < db.left) {
							this->x = db.left + this->size;
						}

						if (bounds.right > db.right) {
							this->x = db.right - this->size;
						}
					}
					else {

						if (bounds.top < db.top) {
							this->y = db.top + this->size;
						}

						if (bounds.bot > db.bot) {
							this->y = db.bot - this->size;
						}
					}
				}
			}

			else {
				this->inDoor = bounds.inRange(d.isHorizontal(), db);
			}

			return;
		}
	}

	this->inDoor = false;
}

void Player::setMovePower(PlayerMovePower mp)
{
	this->movePower = mp;
}

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

void Player::update(Map& m)
{
	if (this->reloading && this->reloadClock.getElapsedTime().asMilliseconds() > PLAYER_RELOAD_COOLDOWN) {
		this->reloading = false;
		this->nBulletes = PLAYER_BULLETES_NUMBER;
	}

	if (this->movePower == PlayerMovePower::FORWARD) {

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

void Player::setDirectionByMousePosition(float x, float y)
{
	this->setDirection(atan2(y - this->y, x - this->x) * 180 / float(PI));
}

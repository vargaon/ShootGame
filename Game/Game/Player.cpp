#include "Player.hpp"

using namespace sf;

void Player::shoot()
{
	if (this->canShoot()) {

		this->shootClock.restart();

		Bullet b;

		b.setStartPosition(this->getPosition());
		b.setDirection(this->getDirection());

		this->bullets.push_back(b);

		--this->bulletesInStack;

		std::cout << "Shot!" << std::endl;

		if (this->bulletesInStack <= 0) {
			this->reload();
		}
	}	
}

int Player::getBulletesInStack()
{
	return this->bulletesInStack;
}

int Player::getCollectedItems()
{
	return this->collectedItems;
}

int Player::getKilledZombies()
{
	return this->killedZombies;
}

int Player::getLives()
{
	return this->lives;
}

void Player::checkForCollectedItems()
{
	for (auto&& i : this->room->items) {

		auto ib = i.getBounds();

		if (this->bounds.inCollisionWith(ib)) {
			i.collect();
			++this->collectedItems;

			std::cout << "Item collected!" << std::endl;
		}
	}
}

void Player::checkForZombies(zombies_con_t& zombies)
{
	auto p = this->getPosition();

	for (auto&& z : zombies) {
		auto zb = z.getBounds();

		if (this->bounds.inCollisionWith(zb)) {
			--this->lives;
			z.die();
			std::cout << "Killed by zombie!" << std::endl;
		}
		else {
			z.setDirectionByPosition(p);
		}
	}
}

void Player::updateBulletes(Map& m, zombies_con_t& zombies)
{
	for (auto it = this->bullets.begin(); it != this->bullets.end();) {

		it->update(m);
		auto bb = it->getBounds();

		for (auto&& z : zombies) {

			auto zb = z.getBounds();

			if (zb.inCollisionWith(bb)) {

				z.die();
				it->destroy();
				++this->killedZombies;

				std::cout << "Killed zombie!" << std::endl;

				break;
			}
		}

		if (!it->isActive()) {
			it = this->bullets.erase(it);
		}
		else {
			it++;
		}
	}
}

void Player::update(Map& m, zombies_con_t& zombies)
{
	//reloading
	if (this->reloading && this->reloadClock.getElapsedTime().asMilliseconds() > PLAYER_RELOAD_COOLDOWN) {
		this->reloading = false;
		this->bulletesInStack = PLAYER_STACK_CAPACITY;
	}

	//move
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

	this->checkForZombies(zombies);
	this->updateBulletes(m, zombies);
}

void Player::render(sf::RenderWindow* window)
{
	MoveableEntity::render(window);

	for (auto&& b : this->bullets) {
		b.render(window);
	}
}

void Player::init()
{
	this->lives = PLAYER_LIVES;
	this->collectedItems = 0;
	this->killedZombies = 0;
	this->bulletesInStack = PLAYER_STACK_CAPACITY;
}

void Player::setup(Room* pRoom)
{
	this->setStartPositionByRoom(pRoom);

	this->reloading = false;
	this->reloadClock.restart();
	this->shootClock.restart();

	this->bullets.clear();
}

bool Player::canShoot()
{
	return (!this->reloading && this->bulletesInStack > 0 && this->shootClock.getElapsedTime().asMilliseconds() > PLAYER_SHOOT_COOLDOWN);
}

void Player::reload()
{
	if (this->reloading || this->bulletesInStack == PLAYER_STACK_CAPACITY) return;

	std::cout << "Reload!" << std::endl;

	this->reloading = true;
	this->reloadClock.restart();
}

bool Player::isReloading()
{
	return this->reloading;
}

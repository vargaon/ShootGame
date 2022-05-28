#include "Player.hpp"

using namespace sf;

bool Player::canShoot()
{
	return (!this->reloading && this->bulletesInStack > 0 && this->shootClock.getElapsedTime().asMilliseconds() > PLAYER_SHOOT_COOLDOWN);
}

bool Player::isReloading()
{
	return this->reloading;
}

int Player::getBulletesInStack()
{
	return this->bulletesInStack;
}

int Player::getTotalCoins()
{
	return this->totalCoins;
}

int Player::getLevelCoins()
{
	return this->levelCoins;
}

int Player::getKilledZombies()
{
	return this->killedZombies;
}

int Player::getLives()
{
	return this->lives;
}

void Player::init()
{
	this->lives = PLAYER_LIVES;
	this->bulletesInStack = PLAYER_STACK_CAPACITY;
	this->totalCoins = 0;
	this->levelCoins = 0;
	this->killedZombies = 0;
}

void Player::setup(Room* startRoom)
{
	this->setStartPositionByRoom(startRoom);

	this->reloading = false;
	this->reloadClock.restart();
	this->shootClock.restart();
	this->bullets.clear();

	this->levelCoins = 0;
}

void Player::shoot()
{
	if (this->canShoot()) {

		this->shootClock.restart();

		Bullet b;

		b.setStartPosition(this->getPosition());
		b.setDirection(this->getDirection());

		this->bullets.push_back(b);

		--this->bulletesInStack;

		//std::cout << "Shot!" << std::endl;

		if (this->bulletesInStack <= 0) {
			this->reload();
		}
	}	
}

void Player::reload()
{
	if (this->reloading || this->bulletesInStack == PLAYER_STACK_CAPACITY) return;

	//std::cout << "Reload!" << std::endl;

	this->reloading = true;
	this->reloadClock.restart();
}

void Player::update(Map& map, zombies_con_t& zombies)
{
	//reloading
	if (this->reloading && this->reloadClock.getElapsedTime().asMilliseconds() > PLAYER_RELOAD_COOLDOWN) {
		this->reloading = false;
		this->bulletesInStack = PLAYER_STACK_CAPACITY;
	}

	this->move(map, PLAYER_MOVE_SPEED);

	this->collectCoins();
	this->observeZombies(zombies);

	this->updateBulletes(map, zombies);
}

void Player::drawAt(sf::RenderWindow* window)
{
	MoveableEntity::drawAt(window);

	for (auto&& b : this->bullets) {
		b.drawAt(window);
	}
}

void Player::collectCoins()
{
	for (auto&& r : this->room->getNeighborhood()) {

		for (auto&& c : r->getCoins()) {

			if (c.tryCollect(this->getBounds())) {
				++this->totalCoins;
				++this->levelCoins;
				//std::cout << "Coin collected!" << std::endl;
			}
		}
	}
}

void Player::observeZombies(zombies_con_t& zombies)
{
	auto p = this->getPosition();

	for (auto&& z : zombies) {
		const auto& zb = z.getBounds();

		if (this->getBounds().inCollisionWith(zb)) {
			--this->lives;
			z.die();
			//std::cout << "Killed by zombie!" << std::endl;
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
		const auto& bb = it->getBounds();

		for (auto&& z : zombies) {

			const auto& zb = z.getBounds();

			if (zb.inCollisionWith(bb)) {

				z.die();
				it->destroy();
				++this->killedZombies;

				//std::cout << "Killed zombie!" << std::endl;

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

#include "Player.hpp"
#include <iostream>

using namespace sf;

Player::Player(float size, sf::Vector2f position): Entity(size, 3, Color::Red, position, -90)
{
}

void Player::TurnLeft()
{
	angle -= PLAYER_TURN_SPEED;
}

void Player::TurnRight()
{
	angle += PLAYER_TURN_SPEED;
}

void Player::MoveForeward()
{
	this->move = PlayerMove::FOREWARD;
}

void Player::MoveBack()
{
	this->move = PlayerMove::BACKWARD;
}

void Player::Stop()
{
	this->move = PlayerMove::STOP;
}

void Player::Shoot(std::vector<Bullet>& bulletes)
{
	if (this->clock.restart().asMilliseconds() > 50) {

		Bullet b(Vector2f(this->x, this->y), this->angle);
		bulletes.push_back(b);
	}
}

void Player::updateByRoom(Room& room)
{
	if (this->x - this->size < room.left + 4.f) {
		this->x = room.left + 4.f + this->size;
	}

	if (this->x + this->size > room.right - 4.f) {
		this->x = room.right - 4.f - this->size;
	}

	if (this->y - this->size < room.top + 4.f) {
		this->y = room.top + 4.f + this->size;
	}

	if (this->y + this->size > room.bot - 4.f) {
		this->y = room.bot - 4.f - this->size;
	}
}

void Player::updateByDoor(Door& door)
{
	if (door.isHorizontal()) {
		if (this->x - this->size < door.getMinBound()) {
			this->x = door.getMinBound() + this->size;
		} 

		if (this->x + this->size > door.getMaxBound()) {
			this->x = door.getMaxBound() - this->size;
		}
	}
	else {
		if (this->y - this->size < door.getMinBound()) {
			this->y = door.getMinBound() + this->size;
		}

		if (this->y + this->size > door.getMaxBound()) {
			this->y = door.getMaxBound() - this->size;
		}
	}
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(this->x, this->y);
}

sf::FloatRect Player::getBounds()
{
	return FloatRect(this->x - this->size, this->y - this->size, this->size * 2, this->size * 2);
}

void Player::Update()
{

	if (this->move == 0) return;

	auto p_directions = computeDirectionsPowers();

	this->x += p_directions.x * this->move * PLAYER_MOVE_SPEED;
	this->y += p_directions.y * this->move * PLAYER_MOVE_SPEED;
}

void Player::Render(sf::RenderWindow& window)
{
	this->entity.setPosition(Vector2f(this->x, this->y));
	this->entity.setRotation(this->angle + 90.f);

	window.draw(this->entity);
}

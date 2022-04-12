#include "Player.hpp"

using namespace sf;

Player::Player(): dx(0.f), dy(0.f), move(0), angle(-90)
{
	initEntity(10.f, 3, Color::Red);
}

void Player::TurnLeft()
{
	angle -= 5;
}

void Player::TurnRight()
{
	angle += 5;
}

void Player::MoveForeward()
{
	this->move = 1;
}

void Player::MoveBack()
{
	this->move = -1;
}

void Player::Stop()
{
	this->move = 0;
}

void Player::Shoot(std::vector<Bullet>& bulletes)
{
	if (this->clock.restart().asMilliseconds() > 50) {

		Bullet b(this->angle);
		b.setStartPosition(Vector2f(this->x, this->y));
		bulletes.push_back(b);
		
	}
}

void Player::Update(Vector2u winSize)
{
	this->dx += cos(this->angle * DEGTORAD);
	this->dy += sin(this->angle * DEGTORAD);

	int maxSpeed = 2;
	float speed = sqrt(this->dx * this->dx + this->dy * this->dy);

	if (speed > maxSpeed)
	{
		this->dx *= maxSpeed / speed;
		this->dy *= maxSpeed / speed;
	}

	float xColision = winSize.x - this->size;
	float yColision = winSize.y - this->size;

	if (this->x > xColision) this->x = xColision; if (this->x < this->size) this->x = this->size;
	if (this->y > yColision) this->y = yColision; if (this->y < this->size) this->y = this->size;

	this->x += this->dx * this->move;
	this->y += this->dy * this->move;
}

void Player::Render(sf::RenderWindow& window)
{
	this->entity.setPosition(Vector2f(this->x, this->y));
	this->entity.setRotation(this->angle + 90.f);

	window.draw(this->entity);
}

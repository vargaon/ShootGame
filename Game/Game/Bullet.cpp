#include "Bullet.hpp"

using namespace sf;

Bullet::Bullet(int angle): active(true)
{
	this->dx = cos(angle * DEGTORAD) * 10;
	this->dy = sin(angle * DEGTORAD) * 10;

	initEntity(2.f, 30, Color::Black);
}

void Bullet::Update(sf::Vector2u winSize)
{
	if (!this->active) return;

	this->x += this->dx;
	this->y += this->dy;

	if (this->x > winSize.x || this->x < 0 || this->y > winSize.y || this->y < 0) this->active = false;
}

void Bullet::Render(sf::RenderWindow& window)
{
	this->entity.setPosition(Vector2f(this->x, this->y));
	window.draw(this->entity);
}

bool Bullet::isNotActive()
{
	return !this->active;
}

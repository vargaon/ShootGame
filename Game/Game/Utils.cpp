#include "Utils.hpp"

Bounds::Bounds(float width, float height, Position p)
{
	this->width = width;
	this->height = height;

	this->updateByPosition(p);
}

float Bounds::getLeft() const
{
	return this->left;
}

float Bounds::getRight() const
{
	return this->right;
}

float Bounds::getTop() const
{
	return this->top;
}

float Bounds::getBot() const
{
	return this->bot;
}

bool Bounds::isIn(const Bounds& b) const
{
	return (
		this->inRange(true, b) &&
		this->inRange(false, b)
		);
}

bool Bounds::inCollisionWith(const Bounds& b) const
{
	return !(
		this->right <= b.left ||
		this->left >= b.right ||
		this->bot <= b.top ||
		this->top >= b.bot
		);
}

bool Bounds::inRange(bool horizontal, const Bounds& b) const
{
	if (horizontal) {
		return (
			this->left >= b.left &&
			this->right <= b.right
			);
	}
	else {
		return (
			this->top >= b.top &&
			this->bot <= b.bot
			);
	}
}

bool Bounds::contains(const Float2Vector& v) const
{
	return (
		this->left <= v.x && 
		this->right >= v.x &&
		this->top <= v.y &&
		this->bot >= v.y
		);
}

void Bounds::updateByPosition(Position p)
{
	this->left = p.x - width / 2;
	this->right = p.x + width / 2;
	this->top = p.y - height / 2;
	this->bot = p.y + height / 2;
}

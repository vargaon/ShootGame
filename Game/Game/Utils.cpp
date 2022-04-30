#include "Utils.hpp"

bool Bounds::inCollisionWith(Bounds& b)
{
	return !(
		this->right <= b.left ||
		this->left >= b.right ||
		this->bot <= b.top ||
		this->top >= b.bot
		);
}

bool Bounds::inRange(bool horizontal, Bounds& b)
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

bool Bounds::contains(Float2Vector& v)
{
	return this->left <= v.x && this->right >= v.y;
}

bool Bounds::isIn(Bounds& b)
{
	return (
		this->inRange(true, b) &&
		this->inRange(false, b)
		);
}

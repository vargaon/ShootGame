#include "Utils.hpp"

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

bool Bounds::isIn(const Bounds& b) const
{
	return (
		this->inRange(true, b) &&
		this->inRange(false, b)
		);
}

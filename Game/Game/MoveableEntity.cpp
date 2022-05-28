#include "MoveableEntity.hpp"

float MoveableEntity::getDirection() const
{
	return this->direction;
}

void MoveableEntity::setDirection(float dir)
{
	this->direction = dir;
	this->setRotation(dir + 90.f);
	this->computeDirectionsPowers();
}

void MoveableEntity::computeDirectionsPowers()
{
	this->dx = cos(this->direction * float(PI) / 180);
	this->dy = sin(this->direction * float(PI) / 180);
}
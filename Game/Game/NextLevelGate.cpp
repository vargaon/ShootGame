#include "NextLevelGate.hpp"

Room* NextLevelGate::getRoom()
{
	return this->room;
}

void NextLevelGate::setPositionByRoom(Room* r)
{
	this->room = r;

	this->setPosition(r->getCentrePosition());
}

bool NextLevelGate::tryEnter(const Bounds& b)
{
	return this->getBounds().inCollisionWith(b);
}

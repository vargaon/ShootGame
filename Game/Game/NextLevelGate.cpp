#include "NextLevelGate.hpp"

NextLevelGate::NextLevelGate()
{
	this->entity.setSize({ GATE_SIZE, GATE_SIZE });
	this->entity.setOrigin(GATE_SIZE / 2, GATE_SIZE / 2);
	this->entity.setFillColor(GATE_COLOR);
}

void NextLevelGate::setPosition(Position p)
{
	this->bounds = Bounds(p.y - GATE_SIZE/2, p.y + GATE_SIZE/2, p.x - GATE_SIZE/2, p.x + GATE_SIZE/2);
	this->entity.setPosition(p.x, p.y);
}

bool NextLevelGate::enteredGate(const Bounds& b)
{
	return this->bounds.inCollisionWith(b);
}

void NextLevelGate::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

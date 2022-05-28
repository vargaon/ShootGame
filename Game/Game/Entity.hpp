#pragma once

#include <SFML/Graphics.hpp> 

#include "Utils.hpp"

class Entity {

public:

	Entity() {};
	Entity(float width, float height) : width(width), height(height), bounds(width, height) {};

	virtual ~Entity() {};

	const Bounds& getBounds() const;
	Position getPosition() const;
	void transpose();

	virtual void drawAt(sf::RenderWindow* window) = 0;

protected:

	void updatePosition(Position p);

private:

	float width = 0.f;
	float height = 0.f;

	Bounds bounds;
	Position position;
};
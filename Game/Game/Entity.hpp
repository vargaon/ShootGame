#pragma once

#include <SFML/Graphics.hpp> 
#include "Bounds.hpp"

float const DEGTORAD = 0.017453f;
const double PI = 3.14159265;

class Entity {

protected:

	float x = 0.f;
	float y = 0.f;
	float size = 0.f;

	sf::CircleShape entity;

public:

	Entity() {};
	Entity(float size, int pointCount, sf::Color color);
	virtual ~Entity() {};

	void setPosition(float x, float y);
	void render(sf::RenderWindow* window);
};

class MoveableEntity : public Entity {

private:

	float direction = 0.f;
	void computeDirectionsPowers(float d);

protected:

	float dx = 0.f;
	float dy = 0.f;
	
	bool inDoor = false;

public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color) : Entity(size, pointCount, color) {};

	Bounds getBounds();

	float getDirection();
	void setDirection(float direction);
};

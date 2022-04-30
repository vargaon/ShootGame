#pragma once

#include <SFML/Graphics.hpp> 
#include "Bounds.hpp"

const double PI = 3.14159265;

class Entity {

private:
	sf::CircleShape entity;

protected:
	float size = 0.f;

	void setPosition(float x, float y);
	void setRotation(float direction);

	Bounds getBounds(float x, float y);

public:

	Entity() {};
	Entity(float size, int pointCount, sf::Color color);
	virtual ~Entity() {};

	void render(sf::RenderWindow* window);
};

class MoveableEntity : public Entity {

private:

	float direction = 0.f;
	void computeDirectionsPowers(float d);

protected:

	float x = 0.f;
	float y = 0.f;

	float dx = 0.f;
	float dy = 0.f;

	Bounds bounds;
	
	bool inDoor = false;

public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color) : Entity(size, pointCount, color) {};

	Bounds getBounds();

	float getDirection();
	void setDirection(float direction);
};

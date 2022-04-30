#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.hpp"

const double PI = 3.14159265;

class Entity {

public:

	Entity() {};
	Entity(float size, int pointCount, sf::Color color);

	virtual ~Entity() {};

	Bounds getBounds();
	Position getPosition();

	void render(sf::RenderWindow* window);

private:

	sf::CircleShape entity;
	Position position;

protected:

	float size = 0.f;
	Bounds bounds;

	void setPosition(Position& p);
	void setRotation(float direction);
};

class MoveableEntity : public Entity {

public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color) : Entity(size, pointCount, color) {};

	float getDirection();
	void setDirection(float direction);

private:

	float direction = 0.f;
	void computeDirectionsPowers(float d);

protected:

	float x = 0.f;
	float y = 0.f;

	float dx = 0.f;
	float dy = 0.f;
	
	bool inDoor = false;
};

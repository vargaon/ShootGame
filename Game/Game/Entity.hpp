#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.hpp"

const double PI = 3.14159265;

class Entity {

public:

	Entity() {};
	Entity(float size, unsigned int pointCount, sf::Color color);

	virtual ~Entity() {};

	Bounds getBounds() const;
	Position getPosition() const;

	void render(sf::RenderWindow* window);

private:

	sf::CircleShape entity;
	Position position;

protected:

	float size = 0.f;
	Bounds bounds;

	void setPosition(Position p);
	void setRotation(float direction);
};

class MoveableEntity : public Entity {

public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color) : Entity(size, pointCount, color) {};

	float getDirection() const;
	void setDirection(float dir);

private:

	float direction = 0.f;
	void computeDirectionsPowers();

protected:

	float x = 0.f;
	float y = 0.f;

	float dx = 0.f;
	float dy = 0.f;
	
	bool inDoor = false;
};

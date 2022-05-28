#pragma once

#include "Entity.hpp"

const double PI = 3.14159265;

class CircleEntity : public Entity {
public:

	CircleEntity() {};
	CircleEntity(float size, unsigned int pointCount, sf::Color color);

	void drawAt(sf::RenderWindow* window);

protected:

	float getSize();
	void setPosition(Position p);
	void setRotation(float direction);

private:

	float size = 0.f;
	sf::CircleShape entity;
	Position position;
};

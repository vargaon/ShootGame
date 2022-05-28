#pragma once

#include "Entity.hpp"

class RectangleEntity : public Entity {
public:

	RectangleEntity() {};
	RectangleEntity(float width, float height, sf::Color color);

	void transpose();
	void drawAt(sf::RenderWindow* window);

protected:

	void setPosition(Position p);

private:
	sf::RectangleShape entity;
};

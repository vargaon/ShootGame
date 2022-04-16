#pragma once

#include <SFML/Graphics.hpp> 

float const DEGTORAD = 0.017453f;

class MoveableEntity {

public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color, sf::Vector2f position, int direction);
	
	virtual ~MoveableEntity() {};

	sf::FloatRect getBounds();
	sf::Vector2f getPosition();

protected:

	sf::CircleShape entity;

	float size = 0.f;

	float x = 0.f;
	float y = 0.f;

	int direction = 0;

	sf::Vector2f computeDirectionsPowers();
};

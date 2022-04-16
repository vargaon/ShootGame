#pragma once

#include <SFML/Graphics.hpp> 

float const DEGTORAD = 0.017453f;

class Entity {

public:

	Entity() {};
	Entity(float size, int nVertices, sf::Color color, sf::Vector2f position, int angle);
	
	virtual ~Entity() {};

	virtual void Update(sf::Vector2u winSize) {};
	virtual void Render(sf::RenderWindow& window) {};

protected:

	float size = 0.f;

	float x = 0.f;
	float y = 0.f;

	int angle = 0;

	sf::CircleShape entity;

	sf::Vector2f computeDirectionsPowers();
};

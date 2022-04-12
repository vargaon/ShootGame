#pragma once

#include <SFML/Graphics.hpp> 

float const DEGTORAD = 0.017453f;

class Entity {

public:

	virtual ~Entity() {};
	Entity(): x(0.f), y(0.f), size(1.f) {};

	virtual void Update(sf::Vector2u winSize) {};
	virtual void Render(sf::RenderWindow& window) {};
	void setStartPosition(sf::Vector2f pos);

protected:

	float x, y, size;
	sf::CircleShape entity;

	void initEntity(float size, int nVertices, sf::Color color);
};

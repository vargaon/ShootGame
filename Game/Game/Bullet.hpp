#pragma once

#include "Entity.hpp"

class Bullet : public Entity {
private:
	float dx, dy;
	bool active;
public:
	Bullet(int angle);
	virtual void Update(sf::Vector2u winSize);
	virtual void Render(sf::RenderWindow& window);
	bool isNotActive();
};
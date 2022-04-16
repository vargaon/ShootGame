#pragma once

#include "Entity.hpp"
#include "Door.hpp"

class Bullet : public Entity {
private:
	float dx, dy;
	bool active;
public:
	Bullet(sf::Vector2f position, int angle);
	virtual void Update(sf::Vector2u winSize, doors_con_t& doors);
	virtual void Render(sf::RenderWindow& window);
	bool isNotActive();
};
#pragma once

#include <SFML/Graphics.hpp> 
#include "Door.hpp"
#include "Room.hpp"

float const DEGTORAD = 0.017453f;
const float PI = 3.14159265;

class MoveableEntity {

private:

	virtual void moveThroughDoors(doors_con_t doors) = 0;
	virtual void moveInRooms(rooms_con_t rooms) = 0;

protected:

	
	float size = 0.f;
	float x = 0.f;
	float y = 0.f;
	bool inDoor = false;
	float direction = 0.f;

	sf::Vector2f computeDirectionsPowers();

public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color);


	virtual ~MoveableEntity() {};

	sf::CircleShape entity;
	sf::FloatRect getBounds();
	sf::Vector2f getPosition();

	virtual void setStartPosition(sf::Vector2f position);

	virtual void update(rooms_con_t& rooms, doors_con_t& doors) = 0;
};

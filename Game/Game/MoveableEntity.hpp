#pragma once

#include "CircleEntity.hpp"

class MoveableEntity : public CircleEntity {
public:

	MoveableEntity() {};
	MoveableEntity(float size, int pointCount, sf::Color color) : CircleEntity(size, pointCount, color) {};

	float getDirection() const;
	void setDirection(float dir);

protected:

	float x = 0.f;
	float y = 0.f;

	float dx = 0.f;
	float dy = 0.f;

	bool inDoor = false;

private:

	float direction = 0.f;

	void computeDirectionsPowers();
};
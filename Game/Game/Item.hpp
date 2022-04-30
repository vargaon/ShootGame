#pragma once
#include "Entity.hpp"

const float ITEM_SIZE = 5;
const int ITEM_POINT_COUNT = 30;

class Item: public Entity {

private:
	bool active = true;

public:

	Bounds bounds;

	Item(float x, float y);

	void collect();
	bool isActive();
};

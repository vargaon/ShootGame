#pragma once
#include <vector>
#include "Entity.hpp"

const float ITEM_SIZE = 5;
const int ITEM_POINT_COUNT = 30;
const int ITEM_ACTIVE_COOLDOWN = 10000;

class Item: public Entity {

private:
	bool active = true;
	sf::Clock activeCooldownClock;

public:

	Bounds bounds;

	Item(float x, float y);

	void update();
	void collect();
	bool isActive();
};

using items_con_t = std::vector<Item>;

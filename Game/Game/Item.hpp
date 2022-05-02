#pragma once
#include <vector>
#include "Entity.hpp"

const float ITEM_SIZE = 5;
const int ITEM_POINT_COUNT = 30;
const int ITEM_ACTIVE_COOLDOWN = 10000;
const sf::Color ITEM_COLOR = { 255, 255, 0, 255 };

class Item: public Entity {

public:

	Item(Position p);

	void update();
	void collect();
	bool isActive() const;

private:
	bool active = true;
	sf::Clock activeCooldownClock;
};

using items_con_t = std::vector<Item>;

#pragma once

#include <SFML/Graphics.hpp> 
#include <vector>
#include <memory>
#include "Bounds.hpp"

const float ITEM_SIZE = 5;
const int ITEM_POINT_COUNT = 30;

enum class ItemType {
	COIN,
	HEARTH,
	BULLETES
};

class Item {

private:
	sf::CircleShape entity;
	bool active = true;

public:

	Bounds bounds;
	Item(ItemType t, float x, float y);
	void render(sf::RenderWindow* window);
	void destroy();
	bool isActive();
};

using item_ptr_t = std::shared_ptr<Item>;
using items_con_t = std::vector<item_ptr_t>;
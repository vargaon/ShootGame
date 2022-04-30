#pragma once

#include <SFML/Graphics.hpp> 
#include <vector>
#include <map>
#include "Entity.hpp"

const float ITEM_SIZE = 5;
const int ITEM_POINT_COUNT = 30;

enum class ItemType {
	COIN,
	HEARTH,
	BULLETES
};

const std::map<ItemType, sf::Color> ITEM_COLOR {

	{ ItemType::COIN, sf::Color::Yellow },
	{ ItemType::HEARTH, sf::Color::Red },
	{ ItemType::BULLETES, sf::Color::Magenta },
};

class Item: public Entity {

private:
	bool active = true;

public:

	Bounds bounds;

	Item(ItemType t, float x, float y);

	void collect();
	bool isActive();
};

using item_ptr_t = std::shared_ptr<Item>;
using items_con_t = std::vector<item_ptr_t>;
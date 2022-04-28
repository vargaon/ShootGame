#pragma once

#include <SFML/Graphics.hpp> 
#include <vector>
#include <memory>

class Item {

private:
	sf::CircleShape entity;

public:

	Item() {};
	virtual ~Item() {};

	void setPosition(sf::Vector2f position);
	//virtual void apply(Player& p) = 0;
};

using item_ptr_t = std::shared_ptr<Item>;
using items_con_t = std::vector<item_ptr_t>;
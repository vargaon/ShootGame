#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Door {

private:

	bool horizontal;
	float size;

	sf::FloatRect bounds;

	float minBound;
	float maxBound;

public:

	sf::RectangleShape entity;

	Door(bool horizontal, float size, float wallThicknes, sf::Vector2f position);

	bool isHorizontal();

	bool intersectDoor(sf::FloatRect rect);
	bool inDoor(sf::FloatRect rect);

	float getMinBound();
	float getMaxBound();

};

using doors_con_t = std::vector<Door>;

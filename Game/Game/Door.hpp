#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Door {

private:

	sf::FloatRect bounds;
	bool horizontal;
	float size;
	float minBound;
	float maxBound;

public:

	sf::RectangleShape entity;

	Door(bool horizontal, float size, float wallThickness, sf::Vector2f position);

	bool isHorizontal();
	bool inDoorRange(sf::FloatRect rect);

	sf::FloatRect getBounds();

	float getMinBound();
	float getMaxBound();

};

using doors_con_t = std::vector<Door>;

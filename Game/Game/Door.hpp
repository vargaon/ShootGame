#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Room.hpp"
#include "Bounds.hpp"

const float DOOR_SIZE = 50.f;

class Door {

private:

	sf::RectangleShape entity;

	bool horizontal;

public:

	Bounds bounds;
	
	Door(bool isHorizontal, float x, float y);

	bool isHorizontal();

	void render(sf::RenderWindow* window);
};

using doors_con_t = std::vector<Door>;

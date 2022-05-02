#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Room.hpp"
#include "Utils.hpp"

const float DOOR_SIZE = 70.f;

class Door {

private:

	sf::RectangleShape entity;

	bool horizontal;

public:

	Bounds bounds;
	
	Door(bool isHorizontal, Position p);

	bool isHorizontal() const;

	void render(sf::RenderWindow* window);
};

using doors_con_t = std::vector<Door>;

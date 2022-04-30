#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.hpp"

class Button
{
public:
	
	Button(std::string btnText, float sizeX, float sizeY);

	void setFont(sf::Font& font);
	void setPosition(float x, float y);
	void render(sf::RenderWindow* window);
	void isMouseOver(float x, float y);

private:

	sf::RectangleShape entity;
	sf::Text text;

	Bounds bounds;

	float x = 0.f;
	float y = 0.f;

	float sizeX = 0.f;
	float sizeY = 0.f;
};
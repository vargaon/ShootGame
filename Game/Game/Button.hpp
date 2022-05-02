#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.hpp"

const int BTN_TEXT_PADDING = 5;

class Button
{
public:
	
	Button();

	void setString(std::string s);
	void setPosition(Position p);
	void setFont(sf::Font& font);
	void setFontSize(unsigned int s);
	void render(sf::RenderWindow* window);
	bool isMouseOver(Position p);

private:

	sf::RectangleShape entity;
	sf::Text text;
	Bounds bounds;

	Float2Vector size;
};
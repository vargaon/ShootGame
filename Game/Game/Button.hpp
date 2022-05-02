#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.hpp"

const int BTN_TEXT_PADDING = 20;

const sf::Color BTN_TEXT_COLOR = { 255, 255, 255, 255 };
const sf::Color BTN_COLOR = { 90, 90, 90, 255 };
const sf::Color BTN_HOVER_COLOR = {100, 100, 100, 255};

class Button {

public:
	
	Button();

	void setString(std::string s);
	void setPosition(Position p);
	void setFont(sf::Font& font);
	void setFontSize(unsigned int s);
	void render(sf::RenderWindow* window);
	bool isMouseOver(Position& p);
	void update(Position& p);

private:

	sf::RectangleShape entity;
	sf::Text text;
	Bounds bounds;

	Float2Vector size;
};
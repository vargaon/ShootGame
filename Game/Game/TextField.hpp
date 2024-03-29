#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Utils.hpp"

const sf::Color TEXT_COLOR = { 255,255,255,255 };

class TextField {

public:

	TextField();
	
	void setPosition(Position p);
	void setFont(sf::Font& font);
	void setFontSize(unsigned int s);
	void setString(std::string s);

	void drawAt(sf::RenderWindow* window);

private:

	sf::Text text;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.hpp"

class TextField {

public:
	TextField();
	
	void setPosition(Position p);
	void setFont(sf::Font& font);
	void setFontSize(unsigned int s);
	void setString(std::string s);
	void render(sf::RenderWindow* window);

private:
	sf::Text text;
};
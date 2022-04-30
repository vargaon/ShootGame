#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.hpp"

class Panel {
private:

	sf::Font font;
	sf::Text infoText;

public:

	Panel();

	void setPosition(float x, float y);

	void updateRunPanel(Player& p);
	void updateEndPanel(Player& p);
	void updateStartPanel();

	void renderRunPanel(sf::RenderWindow* window);
	void renderEndPanel(sf::RenderWindow* window);
	void renderStartPanel(sf::RenderWindow* window);
};
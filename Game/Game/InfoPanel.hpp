#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.hpp"

class InfoPanel {
private:

	sf::Font font;
	sf::Text infoText;

public:

	InfoPanel();

	void setPosition(float x, float y);

	void update(Player& p);
	void render(sf::RenderWindow* window);
};
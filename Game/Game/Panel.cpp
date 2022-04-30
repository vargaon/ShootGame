#include "Panel.hpp"

using namespace sf;

Panel::Panel()
{
	if (!font.loadFromFile("Bodoni.ttf"))
	{
		throw("Font file does not exist!");
	}

	this->infoText.setFont(font);
	this->infoText.setFillColor(Color::Black);
}

void Panel::setPosition(float x, float y)
{
	float yPosition = y + 4;

	this->infoText.setPosition(x + 4, yPosition);
}

void Panel::updateRunPanel(Player& p)
{
	int bulletes = p.getBulletesNumber();
	int items = p.getItemsNumber();
	int lives = p.getLives();

	std::string sep = "  |  ";

	std::stringstream ss;

	ss << "L: " << lives << "/" << PLAYER_LIVES << sep
		<< "I: " << items << sep
		<< "B: " << bulletes << "/" << PLAYER_BULLETES_NUMBER;

	if (p.isReloading()) {
		ss << sep << "R";
	}

	this->infoText.setString(ss.str());
}

void Panel::updateEndPanel(Player& p)
{
}

void Panel::updateStartPanel()
{
}

void Panel::renderRunPanel(sf::RenderWindow* window)
{
	window->draw(this->infoText);
}

void Panel::renderEndPanel(sf::RenderWindow* window)
{
}

void Panel::renderStartPanel(sf::RenderWindow* window)
{
}
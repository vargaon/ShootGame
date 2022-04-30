#include "Button.hpp"

using namespace sf;

Button::Button(std::string btnText, float sizeX, float sizeY)
{
	this->entity.setSize(sf::Vector2f(sizeX, sizeY));
	this->entity.setFillColor(sf::Color::Black);

	this->sizeX = sizeX;
	this->sizeY = sizeY;

	this->text.setString(btnText);
	this->text.setFillColor(sf::Color::White);
}

void Button::setFont(sf::Font& font)
{
}

void Button::setPosition(float x, float y)
{
}

void Button::render(sf::RenderWindow* window)
{
}

void Button::isMouseOver(float x, float y)
{
}

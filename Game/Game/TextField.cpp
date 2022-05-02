#include "TextField.hpp"

TextField::TextField()
{
	this->text.setFillColor(sf::Color::Black);
}

void TextField::setPosition(Position p)
{
	float width = this->text.getLocalBounds().width;
	float height = this->text.getLocalBounds().height;

	this->text.setPosition(p.x - width / 2, p.y - height / 2);
}

void TextField::setFont(sf::Font& font)
{
	this->text.setFont(font);
}

void TextField::setFontSize(unsigned int s)
{
	this->text.setCharacterSize(s);
}

void TextField::setString(std::string s)
{
	this->text.setString(s);
}

void TextField::render(sf::RenderWindow* window)
{
	window->draw(this->text);
}

#include "Button.hpp"

using namespace sf;

Button::Button()
{
	this->entity.setFillColor(BTN_COLOR);
	this->text.setFillColor(BTN_TEXT_COLOR);
}

bool Button::isMouseOver(Position& p)
{
	return this->bounds.contains(p);
}

void Button::setString(std::string s)
{
	this->text.setString(s);

	float sizeX = this->text.getLocalBounds().width + BTN_TEXT_PADDING * 2;
	float sizeY = this->text.getLocalBounds().height + BTN_TEXT_PADDING * 2;

	this->size = Float2Vector(sizeX, sizeY);
	this->entity.setSize({ sizeX, sizeY});
}

void Button::setPosition(Position p)
{
	float bx = p.x - size.x / 2;
	float by = p.y - size.y / 2;

	this->entity.setPosition(bx, by);

	float tx = bx + BTN_TEXT_PADDING;
	float ty = by + BTN_TEXT_PADDING - BTN_TEXT_PADDING/3;

	this->text.setPosition(tx, ty);

	this->bounds = Bounds(size.x, size.y, p);
}

void Button::setFont(sf::Font& font)
{
	this->text.setFont(font);
}

void Button::setFontSize(unsigned int s)
{
	this->text.setCharacterSize(s);
}

void Button::drawAt(sf::RenderWindow* window)
{
	window->draw(this->entity);
	window->draw(this->text);
}

void Button::update(Position& p)
{
	if (this->isMouseOver(p)) {
		this->entity.setFillColor(BTN_HOVER_COLOR);
	}
	else {
		this->entity.setFillColor(BTN_COLOR);
	}
}

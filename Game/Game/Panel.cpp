#include "Panel.hpp"

using namespace sf;

StartPanel::StartPanel()
{
	if (!font.loadFromFile("Bodoni.ttf"))
	{
		throw("Font file does not exist!");
	}

	this->welcomeTextFiled.setFont(this->font);
	this->welcomeTextFiled.setString("Shoot Game!");

	this->startGameBtn.setFont(this->font);
	this->startGameBtn.setString("Play Game");
}

void StartPanel::setup(Position p, Float2Vector size)
{
	float pX = p.x + size.x / 2;
	float pY = p.y + size.y / 2;

	this->welcomeTextFiled.setPosition({ pX, pY - 50 });
	this->startGameBtn.setPosition({ pX, pY + 20 });
}

void StartPanel::render(sf::RenderWindow* window)
{
	this->welcomeTextFiled.render(window);
	this->startGameBtn.render(window);
}

bool StartPanel::update(Position mPosition)
{
	return this->startGameBtn.isMouseOver(mPosition);
}

RunPanel::RunPanel()
{
	if (!font.loadFromFile("Bodoni.ttf"))
	{
		throw("Font file does not exist!");
	}

	this->infoTextField.setFont(this->font);
}

void RunPanel::setup(Position p, Float2Vector size)
{
	Position pField(p.x + (size.x / 2) - 270, p.y + size.y / 2 - 20);
	this->infoTextField.setPosition(pField);
}

void RunPanel::render(sf::RenderWindow* window)
{
	this->infoTextField.render(window);
}

void RunPanel::update(Player& p)
{
	int bulletes = p.getBulletesNumber();
	int items = p.getItemsNumber();
	int lives = p.getLives();

	std::string sep = "  |  ";

	std::stringstream ss;

	ss << sep << "L: " << lives << "/" << PLAYER_LIVES << sep
		<< "I: " << items << sep
		<< "B: " << bulletes << "/" << PLAYER_BULLETES_NUMBER << sep;

	if (p.isReloading()) {
		ss << "R" << sep;
	}

	this->infoTextField.setString(ss.str());
}

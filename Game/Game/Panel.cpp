#include "Panel.hpp"

using namespace sf;

Panel::Panel()
{
	if (!font.loadFromFile("Bodoni.ttf"))
	{
		throw("Font file does not exist!");
	}
}

void Panel::setup(Position p, Float2Vector size)
{
	this->backgroud.setSize({ size.x, size.y });
	this->backgroud.setPosition(p.x, p.y);
	this->backgroud.setFillColor(PANEL_BACKG_COLOR);
}

void Panel::render(sf::RenderWindow* window)
{
	window->draw(this->backgroud);
}

StartPanel::StartPanel()
{
	this->welcomeTextFiled.setFont(this->font);
	this->welcomeTextFiled.setFontSize(60);
	this->welcomeTextFiled.setString("Shoot Game!");
	

	this->startGameBtn.setFont(this->font);
	this->startGameBtn.setFontSize(40);
	this->startGameBtn.setString("Play Game");
}

void StartPanel::setup(Position p, Float2Vector size)
{
	Panel::setup(p, size);

	float cx = p.x + size.x / 2;
	float cy = p.y + size.y / 2;

	this->welcomeTextFiled.setPosition({ cx, cy - 150 });
	this->startGameBtn.setPosition({ cx, cy + 20 });
}

void StartPanel::render(sf::RenderWindow* window)
{
	Panel::render(window);

	this->welcomeTextFiled.render(window);
	this->startGameBtn.render(window);
}

bool StartPanel::update(Position& mPosition, bool mClicked)
{
	this->startGameBtn.update(mPosition);
	return mClicked && this->startGameBtn.isMouseOver(mPosition);
}

EndPanel::EndPanel()
{
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFontSize(60);
	this->gameOverText.setString("Game Over");
	
	this->newGameBtn.setFont(this->font);
	this->newGameBtn.setFontSize(40);
	this->newGameBtn.setString("New Game");

	this->itemSummaryText.setFont(this->font);
	this->itemSummaryText.setString("Items: 0/0");

	this->zombieSummaryText.setFont(this->font);
	this->zombieSummaryText.setString("Zombies: 0/0");
}

void EndPanel::setup(Position pos, Float2Vector panelSize)
{
	Panel::setup(pos, panelSize);

	float cx = pos.x + panelSize.x / 2;
	float cy = pos.y + panelSize.y / 2;

	this->p = { cx, cy };

	this->gameOverText.setPosition({ cx, cy - 150 });
	this->newGameBtn.setPosition({ cx, cy + 100 });
}

void EndPanel::setInfo(int collectedItems, int totalItems, int killedZombies, int totalZombies)
{
	std::stringstream itemSummary;
	itemSummary << "Items: " << collectedItems << "/" << totalItems;
	this->itemSummaryText.setString(itemSummary.str());
	this->itemSummaryText.setPosition({ this->p.x, this->p.y - 50 });

	std::stringstream zombiesSummary;
	zombiesSummary << "Zombies: " << killedZombies << "/" << totalZombies;
	this->zombieSummaryText.setString(zombiesSummary.str());
	this->zombieSummaryText.setPosition({ this->p.x, this->p.y });
}

void EndPanel::render(sf::RenderWindow* window)
{
	Panel::render(window);

	this->gameOverText.render(window);
	this->itemSummaryText.render(window);
	this->zombieSummaryText.render(window);
	this->newGameBtn.render(window);
}

bool EndPanel::update(Position& mPosition, bool mClicked)
{
	this->newGameBtn.update(mPosition);
	return mClicked && this->newGameBtn.isMouseOver(mPosition);
}

RunPanel::RunPanel()
{
	this->infoTextField.setFont(this->font);

	std::string sep = "  |  ";

	std::stringstream ss;

	ss << sep << "L: " << 0 << "/" << PLAYER_LIVES << sep
		<< "I: " << 0 << sep
		<< "B: " << PLAYER_STACK_CAPACITY << "/" << PLAYER_STACK_CAPACITY << sep;

	this->infoTextField.setString(ss.str());
}

void RunPanel::setup(Position p, Float2Vector size)
{
	Panel::setup(p, size);

	Position tp(p.x + size.x / 2, p.y + size.y / 2 - 10);

	this->infoTextPosition = tp;
	this->infoTextField.setPosition(tp);
}

void RunPanel::render(sf::RenderWindow* window)
{
	Panel::render(window);

	this->infoTextField.render(window);
}

void RunPanel::update(Player& p)
{
	int bulletes = p.getBulletesInStack();
	int items = p.getCollectedItems();
	int lives = p.getLives();

	std::string sep = "  |  ";

	std::stringstream ss;

	ss << "L: " << lives << "/" << PLAYER_LIVES << sep
		<< "I: " << items << sep
		<< "B: " << bulletes << "/" << PLAYER_STACK_CAPACITY;

	if (p.isReloading()) {
		ss << sep << "R";
	}

	this->infoTextField.setString(ss.str());
	this->infoTextField.setPosition(this->infoTextPosition);
}

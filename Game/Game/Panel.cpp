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

void Panel::drawAt(sf::RenderWindow* window)
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

bool StartPanel::startGameBtnClicked(Position& mPosition, bool mClicked)
{
	this->startGameBtn.update(mPosition);
	return mClicked && this->startGameBtn.isMouseOver(mPosition);
}

void StartPanel::setup(Position p, Float2Vector size)
{
	Panel::setup(p, size);

	float cx = p.x + size.x / 2;
	float cy = p.y + size.y / 2;

	this->welcomeTextFiled.setPosition({ cx, cy - 150 });
	this->startGameBtn.setPosition({ cx, cy + 20 });
}

void StartPanel::drawAt(sf::RenderWindow* window)
{
	Panel::drawAt(window);

	this->welcomeTextFiled.drawAt(window);
	this->startGameBtn.drawAt(window);
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

bool EndPanel::newGameBtnClicked(Position& mPosition, bool mClicked)
{
	this->newGameBtn.update(mPosition);
	return mClicked && this->newGameBtn.isMouseOver(mPosition);
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

void EndPanel::setup(Position pos, Float2Vector panelSize)
{
	Panel::setup(pos, panelSize);

	float cx = pos.x + panelSize.x / 2;
	float cy = pos.y + panelSize.y / 2;

	this->p = { cx, cy };

	this->gameOverText.setPosition({ cx, cy - 150 });
	this->newGameBtn.setPosition({ cx, cy + 100 });
}

void EndPanel::drawAt(sf::RenderWindow* window)
{
	Panel::drawAt(window);

	this->gameOverText.drawAt(window);
	this->itemSummaryText.drawAt(window);
	this->zombieSummaryText.drawAt(window);
	this->newGameBtn.drawAt(window);
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

void RunPanel::update(Player& p)
{
	int bulletes = p.getBulletesInStack();
	int items = p.getTotalCoins();
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

void RunPanel::drawAt(sf::RenderWindow* window)
{
	Panel::drawAt(window);

	this->infoTextField.drawAt(window);
}

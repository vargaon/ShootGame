#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Button.hpp"
#include "TextField.hpp"
#include "Player.hpp"

const sf::Color PANEL_BACKG_COLOR = { 0, 0, 0, 255 };

class Panel {

public:

	Panel();

	void setup(Position p, Float2Vector size);
	void drawAt(sf::RenderWindow* window);

protected:

	sf::Font font;
	sf::RectangleShape backgroud;
};

class StartPanel: public Panel {

public:

	StartPanel();

	bool startGameBtnClicked(Position& mPosition, bool mClicked);

	void setup(Position p, Float2Vector size);
	void drawAt(sf::RenderWindow* window);

private:

	TextField welcomeTextFiled;
	Button startGameBtn;
};

class EndPanel: public Panel {

public:

	EndPanel();

	bool newGameBtnClicked(Position& mPosition, bool mClicked);

	void setInfo(int collecteItems, int totalItems, int killedZombies, int totalZombies, int reachedLevel);
	void setup(Position pos, Float2Vector panelSize);
	void drawAt(sf::RenderWindow* window);
	
private:

	Position p;
	Float2Vector size;
	Button newGameBtn;
	TextField gameOverText;
	TextField levelSummaryText;
	TextField itemSummaryText;
	TextField zombieSummaryText;
};

class RunPanel: public Panel {

public:

	RunPanel();

	void setup(Position p, Float2Vector size);
	void update(Player& p);
	void drawAt(sf::RenderWindow* window);

private:

	Position infoTextPosition;
	TextField infoTextField;
};
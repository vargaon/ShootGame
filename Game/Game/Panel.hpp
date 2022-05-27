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
	void render(sf::RenderWindow* window);

protected:
	sf::Font font;
	sf::RectangleShape backgroud;
};

class StartPanel: public Panel {

public:
	StartPanel();
	void setup(Position p, Float2Vector size);
	void render(sf::RenderWindow* window);
	bool startGameBtnClicked(Position& mPosition, bool mClicked);

private:
	TextField welcomeTextFiled;
	Button startGameBtn;
};

class EndPanel: public Panel {

public:
	EndPanel();
	void setup(Position pos, Float2Vector panelSize);
	void setInfo(int collecteItems, int totalItems, int killedZombies, int totalZombies);
	void render(sf::RenderWindow* window);
	bool newGameBtnClicked(Position& mPosition, bool mClicked);

private:
	Position p;
	Float2Vector size;
	Button newGameBtn;
	TextField gameOverText;
	TextField itemSummaryText;
	TextField zombieSummaryText;
};

class RunPanel: public Panel {

public:
	RunPanel();
	void setup(Position p, Float2Vector size);
	void render(sf::RenderWindow* window);
	void update(Player& p);

private:
	Position infoTextPosition;
	TextField infoTextField;
};
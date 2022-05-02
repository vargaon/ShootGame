#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Button.hpp"
#include "TextField.hpp"
#include "Player.hpp"

class Panel {
public:
	Panel();
protected:
	sf::Font font;
};

class StartPanel: public Panel {

public:
	StartPanel();
	void setup(Position p, Float2Vector size);
	void render(sf::RenderWindow* window);
	bool update(Position mPosition, bool mClicked);

private:
	TextField welcomeTextFiled;
	Button startGameBtn;
};

class EndPanel: public Panel {

public:
	EndPanel();
	void setup(Position p, Float2Vector size);
	void setInfo(int collecteItems, int totalItems, int killedZombies, int totalZombies);
	void render(sf::RenderWindow* window);
	bool update(Position mPosition, bool mClicked);

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
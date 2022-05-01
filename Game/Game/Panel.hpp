#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Button.hpp"
#include "TextField.hpp"
#include "Player.hpp"

class StartPanel {

public:
	StartPanel();
	void setup(Position p, Float2Vector size);
	void render(sf::RenderWindow* window);
	bool update(Position mPosition);

private:
	sf::Font font;
	TextField welcomeTextFiled;
	Button startGameBtn;
};

class EndPanel {

public:
	void setInfo(int spendTime, int collecteItems, int totalItems, int killedZombies, int totalZombies);
	void render(sf::RenderWindow* window);
	bool update();
};

class RunPanel {

public:
	RunPanel();
	void setup(Position p, Float2Vector size);
	void render(sf::RenderWindow* window);
	void update(Player& p);

private:
	sf::Font font;
	TextField infoTextField;
};
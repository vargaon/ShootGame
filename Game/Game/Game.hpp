#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"

const int WIN_SIZE = 524;
const int INFO_PANEL_SIZE = 75;
const int WIN_FRAME_LIMIT = 60;

class Game {

private:

	sf::Event ev;
	sf::RenderWindow* window = nullptr;

	Map m;
	Player p;
	bulletes_con_t bullets;

	sf::Font font;
	sf::Text playerBulletesInfo;

	void initWindow();
	void initInfoPanel();

	void processInput();
	void updateBullets();
	void updateInfoPanel();

public:

	Game();
	~Game();

	void Update();
	void Render();

	bool IsRunning();
};
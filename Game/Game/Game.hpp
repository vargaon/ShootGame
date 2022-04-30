#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "Player.hpp"
#include "Zombie.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "InfoPanel.hpp"

const int WIN_SIZE = 524;
const int INFO_PANEL_SIZE = 75;
const int WIN_FRAME_LIMIT = 60;

const int MAX_ZOMBIES = 20;
const int ZOMBI_SPAWN_COOLDOWN = 2000;

enum class GameState {
	START,
	RUN,
	END
};

class Game {

private:

	sf::Event ev;
	sf::RenderWindow* window = nullptr;
	InfoPanel infoPanel;

	Map m;
	Player p;
	bulletes_con_t bullets;
	zombies_con_t zombies;

	sf::Clock zombieSpawnClock;

	void initWindow();

	void spawnZombie();

	void processInput();
	void updateBullets();
	void updateZombies();

public:

	Game();
	~Game();

	void Update();
	void Render();

	bool IsRunning();
};
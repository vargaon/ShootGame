#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "Player.hpp"
#include "Zombie.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "Panel.hpp"

const int WIN_SIZE = 524;
const int INFO_PANEL_SIZE = 75;
const int WIN_FRAME_LIMIT = 60;

const int MAX_ZOMBIES = 20;
const int ZOMBI_SPAWN_COOLDOWN = 2000;

const int ITEM_SPAW_COOLDOWN = 2500;

enum class GameState {
	START,
	RUN,
	END
};

class Game {

public:

	Game();
	~Game();

	void update();
	void Render();
	bool IsRunning() const;

private:

	GameState state = GameState::START;

	sf::Event ev;
	sf::RenderWindow* window = nullptr;

	RunPanel runPanel;
	StartPanel startPanel;
	EndPanel endPanel;

	Map m;
	Player p;
	zombies_con_t zombies;

	sf::Clock zombieSpawnClock;
	sf::Clock itemSpawnClock;

	int zombiesSpawned = 0;

	Position mousePosition;
	bool mouseLeftBtnClicked = false;

	void initWindow();
	void setupGame();

	void spawnZombie();
	void updateZombies();

	void spawnItem();

	void updateRunGame();
	void updateStartGame();
	void updateEndGame();

	void processMouseMoved();
	void processMousePressed();

	void renderRunningGame();
};
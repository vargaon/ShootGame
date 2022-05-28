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
#include "LevelSettingParser.hpp"
#include "LevelSetting.hpp"
#include "NextLevelGate.hpp"

const int WIN_SIZE = 524;
const int INFO_PANEL_SIZE = 75;
const int WIN_FRAME_LIMIT = 60;

enum class GameState {
	START,
	RUN,
	END
};

class Game {

public:

	Game();
	~Game();

	bool isRunning() const;

	void update();
	void render();
	
private:

	GameState state = GameState::START;

	sf::Event ev;
	sf::RenderWindow* window = nullptr;

	RunPanel runPanel;
	StartPanel startPanel;
	EndPanel endPanel;

	Map map;
	Player player;
	NextLevelGate levelGate;

	zombies_con_t zombies;

	sf::Clock zombieSpawnClock;
	sf::Clock itemSpawnClock;

	int zombiesSpawned = 0;
	int currentLevel = 0;
	int maxLevel;

	Position mousePosition;
	bool mouseLeftBtnClicked = false;
	bool levelGateActive = false;

	level_setting_con_t levels;
	LevelSetting levelSetting;

	void setupGameLevel(const LevelSetting& levelSetting);
	void initRunningGame();

	void spawnZombie();
	void spawnItem();
	void spawnLevelGate();

	void updateZombies();
	void updatePlayer();
	void updateMap();

	void updateRunningGame();
	void observeStartGamePanel();
	void observeEndGamePanel();

	void observePlayerLives();
	void observeNextLevelGateEntering();

	void nextLevel();

	void processMouseMoved();
	void processMousePressed();

	void renderRunningGame();
};
#include "Game.hpp"

using namespace sf;

Game::Game()
{
	std::srand(42);

	this->window = new RenderWindow(VideoMode(WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE), "Shoot Game!", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(WIN_FRAME_LIMIT);
	
	this->runPanel.setup({ 0, WIN_SIZE }, {WIN_SIZE, INFO_PANEL_SIZE });
	this->startPanel.setup({ 0, 0 }, { WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE });
	this->endPanel.setup({ 0, 0 }, { WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE });

	LevelSettingParser parser;
	this->levels = parser.parse("LevelSettings.txt");
	this->maxLevel = this->levels.size() - 1;
}

Game::~Game()
{
	delete this->window;
}

bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::update()
{
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type)
		{

		case(Event::Closed):
			this->window->close();
			break;

		case(Event::MouseButtonPressed):
			this->processMousePressed();
			break;

		case(Event::MouseMoved):
			this->processMouseMoved();
			break;

		default:
			this->mouseLeftBtnClicked = false;
			break;
		}
	}

	switch (this->state)
	{
	case GameState::START:
		this->observeStartGamePanel();
		break;
	case GameState::RUN:
		this->updateRunningGame();
		break;
	case GameState::END:
		this->observeEndGamePanel();
		break;
	default:
		break;
	}
}

void Game::render()
{
	this->window->clear(sf::Color::White);

	switch (this->state)
	{
	case GameState::START:
		this->startPanel.drawAt(this->window);
		break;
	case GameState::RUN:
		this->renderRunningGame();
		break;
	case GameState::END:
		this->endPanel.drawAt(this->window);
		break;
	default:
		break;
	}

	this->window->display();
}

void Game::setupGameLevel(const LevelSetting& levelSet)
{
	this->zombies.clear();
	this->zombieSpawnClock.restart();

	this->itemSpawnClock.restart();
	this->levelSetting = levelSet;

	this->map.setup(levelSet.mapSetting);

	if (this->levelGate.getRoom() != nullptr) {
		this->player.setup(this->levelGate.getRoom());
	}
	else {
		this->player.setup(this->map.getRandomRoom());
	}

	this->levelGateActive = false;
}

void Game::initRunningGame()
{
	this->state = GameState::RUN;
	this->player.init();
	this->currentLevel = 0;
	this->zombiesSpawned = 0;
	this->coinsCreated = 0;

	this->setupGameLevel(this->levels.at(this->currentLevel));
}

void Game::spawnZombie()
{
	if (int(this->zombies.size()) < this->levelSetting.maxSpawnedZombies && this->zombieSpawnClock.getElapsedTime().asMilliseconds() > this->levelSetting.zombieSpawnCooldown) {

		Room* r = this->map.getRandomRoom(this->player.getRoom()->getNeighborhood());

		this->zombieSpawnClock.restart();

		Zombie z;

		z.setMovePower(PersonMovePower::FORWARD);
		z.setStartPositionByRoom(r);

		this->zombies.push_back(z);

		++this->zombiesSpawned;
	}
}

void Game::updateZombies()
{
	for (auto it = this->zombies.begin(); it != this->zombies.end();) {

		it->update(this->map);

		if (!it->isAlive()) {
			it = this->zombies.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::updatePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->player.setMovePower(PersonMovePower::FORWARD);
	}
	else {
		this->player.setMovePower(PersonMovePower::STOP);
	}

	this->player.update(this->map, this->zombies);
}

void Game::updateMap()
{
	this->map.update();
}

void Game::spawnItem()
{
	if (this->itemSpawnClock.getElapsedTime().asMilliseconds() > this->levelSetting.itemSpawnCooldown) {

		this->itemSpawnClock.restart();
		this->map.createCoin();
		++this->coinsCreated;
	}
}

void Game::spawnLevelGate()
{
	this->levelGate.setPositionByRoom(this->map.getRandomRoom(this->player.getRoom()->getNeighborhood()));
	this->levelGateActive = true;
}

void Game::processMouseMoved()
{
	auto mp = sf::Mouse::getPosition(*this->window);
	this->mousePosition = Position(float(mp.x), float(mp.y));

	if (this->state == GameState::RUN) {
		this->player.setDirectionByPosition(this->mousePosition);
	}
}

void Game::processMousePressed()
{
	if (this->state == GameState::RUN) {
	
		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (this->state == GameState::RUN) {
				this->player.shoot();
			}
		}

		if (Mouse::isButtonPressed(Mouse::Right)) {
			this->player.reload();
		}
	}
	else {
		this->mouseLeftBtnClicked = Mouse::isButtonPressed(Mouse::Left);
	}
}

void Game::updateRunningGame()
{
	this->updateMap();
	this->updatePlayer();

	for (auto&& n : this->player.getRoom()->getNeighborhood()) {
		n->setRoomBackgroupColor(STANDING_ROOM_BACKGROUND_COLOR);
	}

	this->updateZombies();

	this->spawnZombie();
	this->spawnItem();

	if (this->currentLevel != this->maxLevel && !this->levelGateActive && this->player.getLevelCoins() >= this->levelSetting.coinsBeforeNextLevel) {
		this->spawnLevelGate();
	}

	this->runPanel.update(this->player);

	this->observePlayerLives();
	this->observeNextLevelGateEntering();
}

void Game::observePlayerLives()
{
	if (this->player.getLives() <= 0) {

		this->state = GameState::END;

		this->endPanel.setInfo(
			this->player.getTotalCoins(),
			this->coinsCreated,
			this->player.getKilledZombies(),
			this->zombiesSpawned,
			this->currentLevel + 1
		);
	}
}

void Game::observeNextLevelGateEntering()
{
	if (this->levelGateActive && this->levelGate.tryEnter(this->player.getBounds())) {
		this->nextLevel();
	}
}

void Game::nextLevel()
{
	++this->currentLevel;
	this->setupGameLevel(this->levels.at(this->currentLevel));
}

void Game::observeStartGamePanel()
{
	if (this->startPanel.startGameBtnClicked(this->mousePosition, this->mouseLeftBtnClicked)) {

		this->initRunningGame();
	}
}

void Game::observeEndGamePanel()
{
	if (this->endPanel.newGameBtnClicked(this->mousePosition, this->mouseLeftBtnClicked)) {

		this->initRunningGame();
	}
}

void Game::renderRunningGame()
{
	this->map.drawAt(this->window, player.getRoom());

	for (auto&& z : this->zombies) {
		z.drawAt(this->window);
	}

	this->player.drawAt(this->window);

	if (this->levelGateActive) {
		this->levelGate.drawAt(this->window);
	}

	this->runPanel.drawAt(this->window);
}

#pragma once
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

void Game::setupGame(const LevelSetting& levelSetting)
{
	this->zombies.clear();
	this->zombieSpawnClock.restart();
	this->zombiesSpawned = 0;

	this->itemSpawnClock.restart();

	this->levelSetting = levelSetting;

	this->m.setup(levelSetting.s);
	this->p.setup(this->m.getRoom(levelSetting.playerStartRoomId));
}

void Game::spawnZombie()
{
	if (this->zombies.size() < this->levelSetting.maxSpawnedZombies && this->zombieSpawnClock.getElapsedTime().asMilliseconds() > this->levelSetting.zombieSpawnCooldown) {

		Room* r;

		if (this->p.getRoom() != nullptr) {
			r = this->m.getRandomRoom(this->p.getRoom()->id);
		}
		else {
			r = this->m.getRandomRoom();
		}

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

		it->update(this->m);

		if (!it->isAlive()) {
			it = this->zombies.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::spawnItem()
{
	if (this->itemSpawnClock.getElapsedTime().asMilliseconds() > this->levelSetting.itemSpawnCooldown) {

		this->itemSpawnClock.restart();
		this->m.createItem();
	}
}

void Game::processMouseMoved()
{
	auto mp = sf::Mouse::getPosition(*this->window);
	this->mousePosition = Position(float(mp.x), float(mp.y));

	if (this->state == GameState::RUN) {
		this->p.setDirectionByPosition(this->mousePosition);
	}
}

void Game::processMousePressed()
{
	if (this->state == GameState::RUN) {
	
		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (this->state == GameState::RUN) {
				this->p.shoot();
			}
		}

		if (Mouse::isButtonPressed(Mouse::Right)) {
			this->p.reload();
		}
	}
	else {
		this->mouseLeftBtnClicked = Mouse::isButtonPressed(Mouse::Left);
	}
}

void Game::updateRunGame()
{
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->p.setMovePower(PersonMovePower::FORWARD);
	}
	else {
		this->p.setMovePower(PersonMovePower::STOP);
	}

	this->m.update();

	this->p.update(this->m, this->zombies);
	this->updateZombies();

	this->spawnZombie();
	this->spawnItem();

	this->runPanel.update(this->p);

	if (this->p.getLives() <= 0) {
		
		this->state = GameState::END;

		this->endPanel.setInfo(
			this->p.getCollectedItems(),
			this->m.getTotalItems(),
			this->p.getKilledZombies(),
			this->zombiesSpawned
		);
	}
}

void Game::updateStartGame()
{
	if (this->startPanel.update(this->mousePosition, this->mouseLeftBtnClicked)) {

		this->state = GameState::RUN;
		this->p.init();
		this->setupGame(this->levels[this->actualLevel]);
	}
}

void Game::updateEndGame()
{
	if (this->endPanel.update(this->mousePosition, this->mouseLeftBtnClicked)) {

		this->state = GameState::RUN;
		this->p.init();
		this->actualLevel = 0;
		this->setupGame(this->levels[this->actualLevel]);
	}
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
		this->updateStartGame();
		break;
	case GameState::RUN:
		this->updateRunGame();
		break;
	case GameState::END:
		this->updateEndGame();
		break;
	default:
		break;
	}
}

void Game::renderRunningGame()
{
	this->m.render(this->window, p.getRoom());

	for (auto&& z : this->zombies) {
		z.render(this->window);
	}

	this->p.render(this->window);
	this->runPanel.render(this->window);
}

void Game::Render()
{
	this->window->clear(sf::Color::White);

	switch (this->state)
	{
	case GameState::START:
		this->startPanel.render(this->window);
		break;
	case GameState::RUN:
		this->renderRunningGame();
		break;
	case GameState::END:
		this->endPanel.render(this->window);
		break;
	default:
		break;
	}

	this->window->display();
}

bool Game::IsRunning() const
{
	return this->window->isOpen();
}

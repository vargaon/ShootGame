#pragma once
#include "Game.hpp"

using namespace sf;

Game::Game()
{
	this->initWindow();
	
	this->runPanel.setup({ 0, WIN_SIZE }, {WIN_SIZE, INFO_PANEL_SIZE });
	this->startPanel.setup({ 0, 0 }, { WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE });
	this->endPanel.setup({ 0, 0 }, { WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE });
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE), "Shoot Game!", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(WIN_FRAME_LIMIT);
}

void Game::setupGame()
{
	this->state = GameState::RUN;

	this->bullets.clear();
	this->zombies.clear();

	this->zombieSpawnClock.restart();

	this->zombiesSpawned = 0;
	this->killedZombies = 0;

	//TODO: different doors masks

	door_mask_t doorsMask = { {
		{true, true, true, true},
		{false, true, true, false},
		{true, true, true, true},
		{false, true, true, false},
		{true, true, true, true}
	} };

	this->m.setup(doorsMask, doorsMask);
	this->p.setup(this->m.getRoom(12));
}

void Game::spawnZombie()
{
	if (this->zombies.size() < MAX_ZOMBIES && this->zombieSpawnClock.getElapsedTime().asMilliseconds() > ZOMBI_SPAWN_COOLDOWN) {

		auto r = this->m.getRandomRoom();

		if (this->p.getRoom() != nullptr && this->p.getRoom()->id == r->id) {
			return;
		}

		this->zombieSpawnClock.restart();

		Zombie z;

		z.setMovePower(PersonMovePower::FORWARD);
		z.setStartPositionByRoom(r);

		this->zombies.push_back(z);

		++this->zombiesSpawned;
	}
}

void Game::updateBullets()
{
	for (auto it = this->bullets.begin(); it != this->bullets.end();) {

		it->update(this->m);

		if (!it->isActive()) {
			it = this->bullets.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::updateZombies()
{
	for (auto it = this->zombies.begin(); it != this->zombies.end();) {

		it->update(this->m, this->p, this->bullets);

		if (!it->isAlive()) {
			it = this->zombies.erase(it);
			++this->killedZombies;
		}
		else {
			it++;
		}
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
	if (Mouse::isButtonPressed(Mouse::Left)) {

		this->mouseLeftBtnClicked = true;

		if (this->state == GameState::RUN) {
			if (this->p.canShoot()) {
				this->bullets.push_back(this->p.shoot());
			}
		}
	}
	else{ 

		this->mouseLeftBtnClicked = false;

		if (Mouse::isButtonPressed(Mouse::Right)) {

			if (this->state == GameState::RUN) {
				this->p.reload();
			}
		}
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

	this->updateBullets();
	this->p.update(this->m);
	this->updateZombies();
	this->m.update();
	this->spawnZombie();
	this->runPanel.update(this->p);

	if (this->p.getLives() <= 0) {
		
		this->state = GameState::END;

		this->endPanel.setInfo(
			this->p.getCollectedItems(),
			this->m.getTotalItems(),
			this->killedZombies,
			this->zombiesSpawned
		);
	}
}

void Game::updateStartGame()
{
	if (this->startPanel.update(this->mousePosition, this->mouseLeftBtnClicked)) {

		this->setupGame();
	}
}

void Game::updateEndGame()
{
	if (this->endPanel.update(this->mousePosition, this->mouseLeftBtnClicked)) {

		this->setupGame();
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
	this->m.render(this->window);

	for (auto&& b : this->bullets) {
		b.render(this->window);
	}

	for (auto&& z : this->zombies) {
		z.render(this->window);
	}

	this->p.render(this->window);
	this->runPanel.render(this->window);
}

void Game::Render()
{
	this->window->clear(Color::White);

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

bool Game::IsRunning()
{
	return this->window->isOpen();
}

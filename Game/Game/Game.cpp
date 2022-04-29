#pragma once
#include "Game.hpp"

using namespace sf;

Game::Game()
{
	this->initWindow();

	this->initInfoPanel();

	this->p.setPosition(WIN_SIZE / 2, WIN_SIZE / 2);

	this->spawnZombie();
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(WIN_SIZE, WIN_SIZE + INFO_PANEL_SIZE), "My Game!", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(WIN_FRAME_LIMIT);
}

void Game::initInfoPanel()
{
	if (!font.loadFromFile("Bodoni.ttf"))
	{
		throw("Font file does not exist!");
	}

	this->playerBulletesInfo.setFont(font);
	this->playerBulletesInfo.setFillColor(Color::Black);
	this->playerBulletesInfo.setPosition(Vector2f(WIN_SIZE - 100, WIN_SIZE + 20));
}

void Game::spawnZombie()
{
	Zombie z;

	z.setMovePower(PersonMovePower::FORWARD);
	z.setPosition(10, 10);

	this->zombies.push_back(z);
}

void Game::processInput()
{

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->p.setMovePower(PersonMovePower::FORWARD);
	}
	else {
		this->p.setMovePower(PersonMovePower::STOP);
	}

	auto mousePosition = sf::Mouse::getPosition(*this->window);

	this->p.setDirectionByPosition(float(mousePosition.x), float(mousePosition.y));

	if (Mouse::isButtonPressed(Mouse::Right)) {
		this->p.reload();
	}

	if (Mouse::isButtonPressed(Mouse::Left)) {

		if (this->p.canShoot()) {
			this->bullets.push_back(this->p.shoot());
		}
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
		}
		else {
			it++;
		}
	}
}

void Game::updateInfoPanel()
{
	std::string bulletes = this->p.isReloading() ? "R" : std::to_string(this->p.getBulletesNumber());
	this->playerBulletesInfo.setString(bulletes + "/" + std::to_string(PLAYER_BULLETES_NUMBER));
}

void Game::Update()
{
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type)
		{

		case(Event::Closed):

			this->window->close();
			break;

		default:
			break;
		}
	}

	this->processInput();

	this->updateBullets();
	this->p.update(this->m);
	this->updateZombies();
	this->updateInfoPanel();
}

void Game::Render()
{
	this->window->clear(Color::White);

	this->m.render(this->window);

	for (auto&& b : this->bullets) {
		b.render(this->window);
	}

	for (auto&& z : this->zombies) {
		z.render(this->window);
	}

	p.render(this->window);

	this->window->draw(this->playerBulletesInfo);
	this->window->display();
}

bool Game::IsRunning()
{
	return this->window->isOpen();
}

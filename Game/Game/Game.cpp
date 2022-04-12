#pragma once
#include "Game.hpp"
#include <iostream>

using namespace sf;

Game::Game()
{
	this->initWindow();
	this->initPlayer(Vector2f(WIN_H / 2, WIN_W / 2));
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(WIN_H, WIN_W), "My Game!", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initPlayer(sf::Vector2f pos)
{
	this->p.setStartPosition(pos);
}

void Game::updatePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->p.TurnLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->p.TurnRight();
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		this->p.Shoot(this->bullets);
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->p.MoveForeward();
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->p.MoveBack();
	}
	else {
		this->p.Stop();
	}

	this->p.Update(this->window->getSize());
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

	updatePlayer();

	for (auto it = this->bullets.begin(); it != this->bullets.end();) {
		it->Update(this->window->getSize());

		if (it->isNotActive()) {
			it = this->bullets.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::Render()
{
	this->window->clear(Color::White);

	this->p.Render(*this->window);

	for (auto&& b : this->bullets) {
		b.Render(*this->window);
	}

	this->window->display();
}

bool Game::IsRunning()
{
	return this->window->isOpen();
}

#pragma once
#include "Game.hpp"
#include <iostream>

using namespace sf;

Game::Game()
{
	this->initWindow();
	this->initWalls();
	this->initRooms();

	this->initDoors();

	this->p.setStartPosition(Vector2f(WIN_SIZE/2, WIN_SIZE / 2));
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(WIN_SIZE, WIN_SIZE + 75), "My Game!", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::updateBullets()
{
	for (auto it = this->bullets.begin(); it != this->bullets.end();) {

		it->update(this->rooms, this->doors);

		if (!it->isActive()) {
			it = this->bullets.erase(it);
		}
		else {
			it++;
		}
	}
}

void Game::initWalls()
{
	int nRooms = int((WIN_SIZE - WALL_THICKNESS) / (ROOM_SIZE + WALL_THICKNESS));

	for (int i = 0; i <= nRooms; i++) {

		Vector2f vertical_pos(i*(ROOM_SIZE + WALL_THICKNESS), 0);
		Vector2f horizontal_pos(0, i * (ROOM_SIZE + WALL_THICKNESS));

		createWall(true, horizontal_pos);
		createWall(false, vertical_pos);
	}
}

void Game::createWall(bool horizontal, sf::Vector2f position)
{
	Vector2f s;

	if (horizontal) {
		s = Vector2f(WIN_SIZE, WALL_THICKNESS);
	}

	else {
		s = Vector2f(WALL_THICKNESS, WIN_SIZE);
	}

	RectangleShape entity(s);

	entity.setFillColor(Color::Black);
	entity.setPosition(position);

	this->walls.push_back(entity);
}

void Game::processInput()
{
	
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->p.move();
	}
	else {
		this->p.stop();
	}

	this->p.changeDirection(sf::Mouse::getPosition(*this->window));

	if (Keyboard::isKeyPressed(Keyboard::X)) {
		this->p.reload();
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		this->p.shoot(this->bullets);
	}
}

void Game::initRooms()
{
	int nRooms = int((WIN_SIZE - WALL_THICKNESS) / (ROOM_SIZE + WALL_THICKNESS));

	float roomWallSize = ROOM_SIZE + WALL_THICKNESS;

	for (int i = 0; i < nRooms; i++) {

		for (int j = 0; j < nRooms; j++) {

			this->rooms.push_back(Room(
				i * roomWallSize, 
				j * roomWallSize, 
				roomWallSize + WALL_THICKNESS + i * roomWallSize, 
				roomWallSize + WALL_THICKNESS + j * roomWallSize, 
				WALL_THICKNESS));
		}
	}
}

void Game::initDoors()
{
	bool doorsMask[5][4];

	doorsMask[0][0] = false;
	doorsMask[0][1] = false;
	doorsMask[0][2] = false;
	doorsMask[0][3] = false;

	doorsMask[1][1] = false;
	doorsMask[1][2] = false;

	doorsMask[2][0] = false;
	doorsMask[2][1] = false;
	doorsMask[2][2] = false;
	doorsMask[2][3] = false;

	doorsMask[3][1] = false;
	doorsMask[3][2] = false;

	doorsMask[4][0] = false;
	doorsMask[4][1] = false;
	doorsMask[4][2] = false;
	doorsMask[4][3] = false;

	this->createDoors(false, doorsMask);
	this->createDoors(true, doorsMask);
}

void Game::createDoors(bool horizontal, bool mask[5][4])
{

	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 4; j++) {

			if (!mask[i][j]) {

				float x = (i) * (WALL_THICKNESS + ROOM_SIZE) + WALL_THICKNESS + ((ROOM_SIZE - DOOR_SIZE) / 2);
				float y = (j + 1) * (WALL_THICKNESS + ROOM_SIZE);

				if (horizontal) {
					this->doors.push_back(Door(horizontal, DOOR_SIZE, WALL_THICKNESS, Vector2f(x, y)));
				}
				else {
					this->doors.push_back(Door(horizontal, DOOR_SIZE, WALL_THICKNESS, Vector2f(y, x)));
				}
			}
		}
	}
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
	this->p.update(this->rooms, this->doors);
}

void Game::Render()
{
	this->window->clear(Color::White);

	for (auto&& b : this->bullets) {
		this->window->draw(b.entity);
	}

	for (auto&& w : this->walls) {
		this->window->draw(w);
	}

	this->window->draw(p.entity);

	for (auto&& d : this->doors) {
		this->window->draw(d.entity);
	}

	this->window->display();
}

bool Game::IsRunning()
{
	return this->window->isOpen();
}

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

	this->initPlayer(Vector2f(WIN_SIZE/2, WIN_SIZE / 2));
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(WIN_SIZE, WIN_SIZE), "My Game!", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initPlayer(sf::Vector2f position)
{
	this->p = Player(PLAYER_SIZE, position);
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

	this->p.Update();


	auto p_bounds = this->p.getBounds();

	for (auto&& d : this->doors) {
		if (d.intersectDoor(p_bounds)) {
			if (this->p.inDoor) {
				this->p.updateByDoor(d);
				return;
			}
			else {
				if (d.inDoor(p_bounds)) {
					this->p.inDoor = true;
					return;
				}
				else {
					break;
				}
			}
		}
	}

	this->p.inDoor = false;


	int room_num = 0;

	for (auto&& r : this->rooms) {

		room_num++;
		if (r.inRoom(this->p.getPosition(), PLAYER_SIZE)) {
			//std::cout << "Room num: " << room_num << std::endl;
			this->p.updateByRoom(r);
			break;
		}
	}
}

void Game::initWalls()
{
	for (int i = 0; i <= N_ROOMS; i++) {

		Vector2f vertical_pos(WIN_SIZE / N_ROOMS * i, 0);
		Vector2f horizontal_pos(0, WIN_SIZE / N_ROOMS * i);

		createWall(true, horizontal_pos);
		createWall(false, vertical_pos);
	}
}

void Game::createWall(bool horizontal, sf::Vector2f position)
{
	Vector2f s;

	if (horizontal) {
		s = Vector2f(WIN_SIZE, WALL_THICKNES);
	}

	else {
		s = Vector2f(WALL_THICKNES, WIN_SIZE);
	}

	RectangleShape entity(s);

	entity.setFillColor(Color::Black);
	entity.setPosition(position);

	this->walls_entities.push_back(entity);
}

void Game::initRooms()
{
	float left;
	float right;
	float top;
	float bot;

	float roomSize = 100.f + WALL_THICKNES;

	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 5; j++) {

			top = i * roomSize;
			left = j * roomSize;
			bot = roomSize + WALL_THICKNES + i * roomSize;
			right = roomSize + WALL_THICKNES + j * roomSize;

			this->rooms.push_back(Room(top, left, bot, right));

		}
	}
}

void Game::initDoors()
{
	this->doors.push_back(Door(true, DOOR_SIZE, WALL_THICKNES, Vector2f(WIN_SIZE / 5 * 3 - 75, WIN_SIZE / 5 * 3)));
	this->doors.push_back(Door(true, DOOR_SIZE, WALL_THICKNES, Vector2f(WIN_SIZE / 5 * 4 - 75, WIN_SIZE / 5 * 3)));

	this->doors.push_back(Door(false, DOOR_SIZE, WALL_THICKNES, Vector2f(WIN_SIZE / 5 * 3, WIN_SIZE / 5 * 3 - 75)));
	this->doors.push_back(Door(false, DOOR_SIZE, WALL_THICKNES, Vector2f(WIN_SIZE / 5 * 3, WIN_SIZE / 5 * 4 - 75)));
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
		it->Update(this->window->getSize(), this->doors);

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

	

	for (auto&& b : this->bullets) {
		b.Render(*this->window);
	}

	for (auto&& w : this->walls_entities) {

		this->window->draw(w);
	}

	for (auto&& d : this->doors) {
		this->window->draw(d.entity);
	}

	this->p.Render(*this->window);

	this->window->display();
}

bool Game::IsRunning()
{
	return this->window->isOpen();
}

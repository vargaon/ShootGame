#pragma once
#include <SFML/Graphics.hpp> 
#include "Player.hpp"
#include "Door.hpp"
#include <vector>

#include "Room.hpp"

const int WIN_SIZE = 524;
const float WALL_THICKNES = 4.f;
const float PLAYER_SIZE = 10.f;

const int DOOR_SIZE = 50;

const int N_ROOMS = 5;

class Game {

private:

	sf::Event ev;
	sf::RenderWindow* window = nullptr;

	Player p;

	std::vector<Bullet> bullets;

	std::vector<sf::RectangleShape> walls_entities;

	std::vector<Room> rooms;

	doors_con_t doors;

	void initWindow();

	void initPlayer(sf::Vector2f position);
	void initWalls();
	void initRooms();

	void createWall(bool horizontal, sf::Vector2f position);


	void initDoors();

	void updatePlayer();

public:

	Game();
	~Game();

	void Update();
	void Render();
	bool IsRunning();
};
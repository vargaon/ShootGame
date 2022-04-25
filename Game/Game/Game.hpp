#pragma once
#include <SFML/Graphics.hpp> 
#include "Player.hpp"
#include "Door.hpp"
#include "Room.hpp"
#include <vector>

const int WIN_SIZE = 524;
const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;
const float DOOR_SIZE = 50.f;

class Game {

private:

	sf::Event ev;
	sf::RenderWindow* window = nullptr;

	Player p;
	bulletes_con_t bullets;

	std::vector<sf::RectangleShape> walls;

	rooms_con_t rooms;
	doors_con_t doors;

	void initWindow();
	void initWalls();
	void initRooms();
	void initDoors();

	void initPlayer(sf::Vector2f position);

	void createWall(bool horizontal, sf::Vector2f position);
	void createDoors(bool horizontal, bool mask[5][4]);

	void processInput();
	void updateBullets();

public:

	Game();
	~Game();

	void Update();
	void Render();

	bool IsRunning();
};
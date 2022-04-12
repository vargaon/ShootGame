#pragma once
#include <SFML/Graphics.hpp> 
#include "Player.hpp"
#include <vector>

const int WIN_H = 500;
const int WIN_W = 500;

class Game {
private:

	sf::Event ev;
	sf::RenderWindow* window = nullptr;

	Player p;

	std::vector<Bullet> bullets;

	void initWindow();
	void initPlayer(sf::Vector2f pos);
	void updatePlayer();

public:

	Game();
	~Game();
	void Update();
	void Render();
	bool IsRunning();
};
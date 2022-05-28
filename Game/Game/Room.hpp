#pragma once

#include <iostream>
#include <vector>

#include "Utils.hpp"
#include "Coin.hpp"

const float WALL_THICKNESS = 4.f;
const float ROOM_SIZE = 100.f;
const int ROOM_PADDING = 15;
const sf::Color ROOM_BACKGROUND_COLOR = { 140,140,140,255 };

class Room;

using neighbor_rooms_con_t = std::vector<Room*>;

class Room {

public:

	Room() {};
	Room(int id, Position p);

	void createCoin();

	Position getRandomPosition() const;
	Position getCentrePosition() const;

	int getId() const;
	coins_con_t& getCoins();
	const neighbor_rooms_con_t& getNeighborhood() const;

	const Bounds& getOuterBounds() const;
	const Bounds& getInnerBounds() const;

	void setRoomBackgroupColor(sf::Color color);

	void update();
	void clear();

	void drawBackgroundAt(sf::RenderWindow* window);
	void drawItemsAt(sf::RenderWindow* window);

	void addNeighbor(Room* room);

private:

	int id = 0;

	Position centrePosition;

	Bounds outerBounds;
	Bounds innerBounds;
	Bounds spawnRange;

	coins_con_t items;
	neighbor_rooms_con_t neighborhood;

	sf::RectangleShape background;

	void updateItems();
};

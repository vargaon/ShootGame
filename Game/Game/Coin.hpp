#pragma once

#include <vector>

#include "CircleEntity.hpp"

const float COIN_SIZE = 5.f;
const int COIN_POINT_COUNT = 30;
const int COIN_ACTIVE_COOLDOWN = 10000;
const sf::Color COIN_COLOR = { 255, 255, 0, 255 };

class Coin: public CircleEntity {

public:

	Coin(Position p);

	bool isActive() const;

	bool tryCollect(const Bounds& b);
	void update();

private:

	bool active = true;
	sf::Clock activeCooldownClock;
};

using coins_con_t = std::vector<Coin>;

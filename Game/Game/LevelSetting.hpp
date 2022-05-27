#pragma once

#include <vector>
#include "MapSetting.hpp"

class LevelSetting {
public:

	int itemSpawnCooldown = 2500;
	int zombieSpawnCooldown = 2000;
	int playerStartRoomId = 12;
	int maxSpawnedZombies = 20;
	int coinsBeforeNextLevel = 15;

	MapSetting mapSetting;

	LevelSetting() {};
};

using level_setting_con_t = std::vector<LevelSetting>;
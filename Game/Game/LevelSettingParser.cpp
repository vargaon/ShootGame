#include "LevelSettingParser.hpp"

level_setting_con_t LevelSettingParser::parse(const std::string& filename)
{

	std::ifstream fs(filename);

	level_setting_con_t levels;
	std::string line;

	while (fs.good()) {
		levels.push_back(this->parseLevelSetting(fs));
		getline(fs, line);
	}
	
	return levels;
}

LevelSetting LevelSettingParser::parseLevelSetting(std::ifstream& fs)
{
	LevelSetting levelSetting;

	levelSetting.zombieSpawnCooldown = this->parseIntValue(fs);
	levelSetting.maxSpawnedZombies = this->parseIntValue(fs);

	levelSetting.itemSpawnCooldown = this->parseIntValue(fs);
	levelSetting.coinsBeforeNextLevel = this->parseIntValue(fs);

	levelSetting.mapSetting = this->parseMapSetting(fs);

	return levelSetting;
}

MapSetting LevelSettingParser::parseMapSetting(std::ifstream& fs)
{
	door_mask_t horizontalDoorMask;
	door_mask_t verticalDoorMask;

	horizontalDoorMask.fill({false, false, false, false});
	verticalDoorMask.fill({ false, false, false, false });

	std::string line;

	getline(fs, line);

	char c;

	for (int i = 0; i < 9; i++) {

		getline(fs, line);

		for (int j = 1; j < 10; j++) {

			c = line[j];

			if (i % 2 == 0) {

				if (j % 2 == 0) {
					verticalDoorMask[i / 2][(j - 1) / 2] = c == 'd';
				}
			}
			else {

				if (j % 2 == 1) {
					horizontalDoorMask[(j - 1) / 2][i / 2] = c == 'd';
				}
			}
		}
	}

	getline(fs, line);

	return MapSetting(horizontalDoorMask, verticalDoorMask);	
}

int LevelSettingParser::parseIntValue(std::ifstream& fs)
{
	std::stringstream ss;
	std::string line;
	int value;

	getline(fs, line);

	ss << line;
	ss >> value;

	return value;
}

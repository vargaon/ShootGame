#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include "LevelSetting.hpp"

class LevelSettingParser {
public:
	level_setting_con_t parse(const std::string& filename);

private:
	LevelSetting parseLevelSetting(std::ifstream& fs);
	MapSetting parseMapSetting(std::ifstream& fs);
	int parseIntValue(std::ifstream& fs);
};

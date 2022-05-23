#include "MapSetting.hpp"

MapSetting::MapSetting(door_mask_t horizontalDoorMask, door_mask_t verticalDoorMask, sf::Color backgroundColor)
{
	this->horizontalDoorMask = horizontalDoorMask;
	this->verticalDoorMask = verticalDoorMask;
	this->backgroundColor = backgroundColor;
}

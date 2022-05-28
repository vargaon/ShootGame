#include "MapSetting.hpp"

MapSetting::MapSetting(door_mask_t horizontalDoorMask, door_mask_t verticalDoorMask)
{
	this->horizontalDoorMask = horizontalDoorMask;
	this->verticalDoorMask = verticalDoorMask;
}

#pragma once

#include <array>

#include "Room.hpp"
#include "Door.hpp"

const int NUM_OF_ROOM_PER_LINE = 5;

using door_mask_t = std::array<std::array<bool, NUM_OF_ROOM_PER_LINE - 1>, NUM_OF_ROOM_PER_LINE>;

class MapSetting {

public:

	door_mask_t horizontalDoorMask = door_mask_t();
	door_mask_t verticalDoorMask = door_mask_t();

	MapSetting() {};
	MapSetting(door_mask_t horizontalDoorMask, door_mask_t verticalDoorMask);
};
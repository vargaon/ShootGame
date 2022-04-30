#include "Item.hpp"

Item::Item(ItemType t, float x, float y) : Entity(ITEM_SIZE, ITEM_POINT_COUNT, ITEM_COLOR.find(t)->second)
{
	this->setPosition(x, y);
	this->bounds = this->getBounds(x, y);
}

void Item::collect()
{
	this->active = false;
}

bool Item::isActive()
{
	return active;
}

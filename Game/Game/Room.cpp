#include "Room.hpp"

using namespace sf;

Room::Room(float top, float left, float bot, float right, float wallThickness): top(top), left(left), bot(bot), right(right), wallThickness(wallThickness)
{
	this->localBounds = FloatRect(left + wallThickness, top + wallThickness, right - left - 2 * wallThickness, bot - top - 2 * wallThickness);
}

bool Room::inRoom(sf::FloatRect rect)
{
	return (rect.left >= this->left && rect.left + rect.width <= this->right) && (rect.top >= this->top && rect.top + rect.height <= this->bot);
}

bool Room::inLocalBounds(sf::FloatRect rect)
{
	return (rect.left >= this->localBounds.left && rect.left + rect.width <= this->localBounds.left + this->localBounds.width) && 
		(rect.top >= this->localBounds.top && rect.top + rect.height <= this->localBounds.top + this->localBounds.height);
}

void Room::addItem(item_ptr_t i, RoomPosition p)
{
	//TODO: set item position
	this->items.push_back(std::move(i));
}

sf::FloatRect Room::getLocalBounds()
{
	return this->localBounds;
}

void Room::print()
{
	std::cout << "Top: " << this->top << " Left: " << this->left << " Bot: " << this->bot << " Right: " << this->right << std::endl;
}

#include "Room.hpp"

bool Room::inRoom(sf::Vector2f position, float size)
{
	return (position.x - size >= this->left && position.x + size <= this->right) && (position.y - size >= this->top && position.y + size <= this->bot);
}

void Room::print()
{
	std::cout << "Top: " << this->top << " Left: " << this->left << " Bot: " << this->bot << " Right: " << this->right << std::endl;
}

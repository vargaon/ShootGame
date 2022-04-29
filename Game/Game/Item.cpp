#include "Item.hpp"

Item::Item(ItemType t, float x, float y)
{
	this->entity.setRadius(ITEM_SIZE);
	this->entity.setPointCount(ITEM_POINT_COUNT);
	this->entity.setOrigin(ITEM_SIZE, ITEM_SIZE);
	this->entity.setPosition(x, y);

	switch (t)
	{
	case ItemType::COIN:
		this->entity.setFillColor(sf::Color::Yellow);
		break;
	case ItemType::HEARTH:
		this->entity.setFillColor(sf::Color::Red);
	case ItemType::BULLETES:
		this->entity.setFillColor(sf::Color::Cyan);
	default:
		break;
	}
}

void Item::render(sf::RenderWindow* window)
{
	window->draw(this->entity);
}

void Item::destroy()
{
	this->active = false;
}

bool Item::isActive()
{
	return active;
}

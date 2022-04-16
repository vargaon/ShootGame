#include "Bullet.hpp"

using namespace sf;

Bullet::Bullet(sf::Vector2f position, int direction): MoveableEntity(BULLET_SIZE, BULLET_POINT_COUNT, Color::Black, position, direction), active(true)
{
	auto p_directions = computeDirectionsPowers();

	this->dx = p_directions.x;
	this->dy = p_directions.y;
}

bool Bullet::movementThroughDoor(doors_con_t doors)
{
	auto bounds = this->getBounds();

	for (auto&& d : doors) {

		auto d_bounds = d.getBounds();

		if (bounds.intersects(d_bounds) && d.inDoorRange(bounds)) {
			return true;
		}
	}

	return false;
}

void Bullet::movementInRoom(rooms_con_t rooms)
{
	auto bounds = this->getBounds();

	for (auto&& r : rooms) {

		if (r.inLocalBounds(bounds)) {

			return;
		}
	}

	this->active = false;
}

void Bullet::update(rooms_con_t& rooms, doors_con_t& doors)
{
	if (!this->active) return;

	float movePartX = this->dx * BULLET_MOVE_SPEED / BULLET_SPLIT_FRAME_COUNT;
	float movePartY = this->dy * BULLET_MOVE_SPEED / BULLET_SPLIT_FRAME_COUNT;

	for (int i = 0; i < BULLET_SPLIT_FRAME_COUNT; i++) {

		this->x += movePartX;
		this->y += movePartY;


		if (!this->movementThroughDoor(doors)) {
			this->movementInRoom(rooms);
		}

		if (!this->active) break;
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	this->entity.setPosition(Vector2f(this->x, this->y));
	window.draw(this->entity);
}

bool Bullet::isActive()
{
	return this->active;
}

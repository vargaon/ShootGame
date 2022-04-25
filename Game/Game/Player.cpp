#include "Player.hpp"
#include <iostream>

using namespace sf;

Player::Player(sf::Vector2f position): MoveableEntity(PLAYER_SIZE, PLAYER_POINT_COUNT, Color::Red, position, -90)
{
}

void Player::turnLeft()
{
	direction -= PLAYER_TURN_SPEED;
}

void Player::turnRight()
{
	direction += PLAYER_TURN_SPEED;
}

void Player::goForward()
{
	this->move = PlayerMove::FORWARD;
}

void Player::goBack()
{
	this->move = PlayerMove::BACKWARD;
}

void Player::stop()
{
	this->move = PlayerMove::STOP;
}

void Player::shoot(std::vector<Bullet>& bulletes)
{
	if (this->clock.restart().asMilliseconds() > PLAYER_SHOOT_COOLDOWN) {

		Bullet b(Vector2f(this->x, this->y), this->direction);
		bulletes.push_back(b);
	}
}

void Player::update(rooms_con_t& rooms, doors_con_t& doors)
{
	auto p_directions = computeDirectionsPowers();

	this->x += p_directions.x * int(this->move) * PLAYER_MOVE_SPEED;
	this->y += p_directions.y * int(this->move) * PLAYER_MOVE_SPEED;

	this->moveThroughDoors(doors);
	this->moveInRooms(rooms);

	this->entity.setPosition(Vector2f(this->x, this->y));
	this->entity.setRotation(this->direction + 90.f);
}

void Player::moveThroughDoors(doors_con_t doors)
{
	auto bounds = this->getBounds();

	bool state = false;

	for (auto&& d : doors) {

		auto d_bounds = d.getBounds();

		if (bounds.intersects(d_bounds)) {

			if (this->inDoor) {

				this->updateByDoor(d);
				state = true;
				break;
			}

			else {

				if (d.inDoorRange(bounds)) {

					this->inDoor = true;
					state = true;
				}

				break;
			}
		}
	}

	if(!state) this->inDoor = false;
}

void Player::moveInRooms(rooms_con_t rooms)
{
	if (this->inDoor) return;

	auto bounds = this->getBounds();

	for (auto&& r : rooms) {
		if (r.inRoom(bounds)) {
			this->updateByRoom(r);
			break;
		}
	}
}

void Player::updateByRoom(Room& room)
{
	auto bounds = room.getLocalBounds();

	float roomLeft = bounds.left;
	float roomRight = bounds.left + bounds.width;
	float roomTop = bounds.top;
	float roomBot = bounds.top + bounds.height;

	if (this->x - this->size < roomLeft) {
		this->x = roomLeft + this->size;
	}

	if (this->x + this->size > roomRight) {
		this->x = roomRight - this->size;
	}

	if (this->y - this->size < roomTop) {
		this->y = roomTop + this->size;
	}

	if (this->y + this->size > roomBot) {
		this->y = roomBot - this->size;
	}
}

void Player::updateByDoor(Door& door)
{
	if (door.isHorizontal()) {
		if (this->x - this->size < door.getMinBound()) {
			this->x = door.getMinBound() + this->size;
		} 

		if (this->x + this->size > door.getMaxBound()) {
			this->x = door.getMaxBound() - this->size;
		}
	}
	else {
		if (this->y - this->size < door.getMinBound()) {
			this->y = door.getMinBound() + this->size;
		}

		if (this->y + this->size > door.getMaxBound()) {
			this->y = door.getMaxBound() - this->size;
		}
	}
}

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
	if (this->clock.restart().asMilliseconds() > 50) {

		Bullet b(Vector2f(this->x, this->y), this->direction);
		bulletes.push_back(b);
	}
}

void Player::update(rooms_con_t& rooms, doors_con_t& doors)
{
	if (this->move == PlayerMove::STOP) return;

	auto p_directions = computeDirectionsPowers();

	this->x += p_directions.x * int(this->move) * PLAYER_MOVE_SPEED;
	this->y += p_directions.y * int(this->move) * PLAYER_MOVE_SPEED;

	if (!this->movementThroughDoor(doors)) {

		this->movementInRoom(rooms);
	}
}

void Player::render(sf::RenderWindow& window)
{
	this->entity.setPosition(Vector2f(this->x, this->y));
	this->entity.setRotation(this->direction + 90.f);

	window.draw(this->entity);
}


bool Player::movementThroughDoor(doors_con_t doors)
{
	auto bounds = this->getBounds();

	bool state = false;

	for (auto&& d : doors) {

		auto d_bounds = d.getBounds();

		if (bounds.intersects(d_bounds)) {

			if (this->lastInDoor) {

				this->updateByDoor(d);
				state = true;
				break;
			}

			else {

				if (d.inDoorRange(bounds)) {

					this->lastInDoor = true;
					state = true;
				}

				break;
			}
		}
	}

	if(!state) this->lastInDoor = false;

	return state;
}

void Player::movementInRoom(rooms_con_t rooms)
{
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

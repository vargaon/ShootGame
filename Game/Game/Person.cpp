#include "Person.hpp"

Room* Person::getRoom() const
{
	return this->room;
}

void Person::setMovePower(PersonMovePower mp)
{
	this->movePower = mp;
}

void Person::setDirectionByPosition(Position& p)
{
	this->setDirection(atan2(p.y - this->y, p.x - this->x) * 180 / float(PI));
}

void Person::setStartPositionByRoom(Room* startRoom)
{
	this->room = startRoom;
	auto p = startRoom->getCentrePosition();

	this->x = p.x;
	this->y = p.y;

	this->setPosition(p);
}

void Person::move(Map& map, float speed)
{
	if (this->movePower == PersonMovePower::FORWARD) {

		this->x += this->dx * speed;
		this->y += this->dy * speed;

		this->setPosition({ this->x, this->y });

		bool wasInDoor = this->inDoor;

		this->moveInDoors(map.doors);

		if (!this->inDoor) {
			this->moveInRooms(map.rooms, wasInDoor);
		}
	}
}

bool Person::inRoom(const Room& r) const
{
	return this->getBounds().isIn(r.getOuterBounds());
}

void Person::moveInRoom(const Room& r)
{
	const auto& roomBounds = r.getInnerBounds();

	auto personBounds = this->getBounds();

	if (!personBounds.isIn(roomBounds)) {

		if (personBounds.getLeft() < roomBounds.getLeft()) {
			this->x = roomBounds.getLeft() + this->getSize();
		}

		if (personBounds.getRight() > roomBounds.getRight()) {
			this->x = roomBounds.getRight() - this->getSize();
		}

		if (personBounds.getTop() < roomBounds.getTop()) {
			this->y = roomBounds.getTop() + this->getSize();
		}

		if (personBounds.getBot() > roomBounds.getBot()) {
			this->y = roomBounds.getBot() - this->getSize();
		}

		this->setPosition({ this->x, this->y });
	}
}

void Person::moveInRooms(rooms_con_t& rooms, bool mayChangeRoom)
{
	if (!mayChangeRoom) {
		this->moveInRoom(*this->room);
	}
	else {
		for (auto&& roomRow : rooms) {

			for (auto&& r : roomRow) {
				if (this->inRoom(r)) {

					this->room = &r;
					this->moveInRoom(*this->room);
					break;
				}
			}
		}
	}
}

void Person::moveInDoors(const doors_con_t& doors)
{
	for (auto&& d : doors) {

		auto doorBounds = d.getBounds();
		auto personBounds = this->getBounds();

		if (personBounds.inCollisionWith(doorBounds)) {

			if (this->inDoor) {

				if (!personBounds.inRange(d.isHorizontal(), doorBounds)) {

					if (d.isHorizontal()) {

						if (personBounds.getLeft() < doorBounds.getLeft()) {
							this->x = doorBounds.getLeft() + this->getSize();
						}

						if (personBounds.getRight() > doorBounds.getRight()) {
							this->x = doorBounds.getRight() - this->getSize();
						}
					}
					else {

						if (personBounds.getTop() < doorBounds.getTop()) {
							this->y = doorBounds.getTop() + this->getSize();
						}

						if (personBounds.getBot() > doorBounds.getBot()) {
							this->y = doorBounds.getBot() - this->getSize();
						}
					}

					this->setPosition({ this->x, this->y });
				}
			}

			else {
				if (personBounds.inRange(d.isHorizontal(), doorBounds)) {
					this->inDoor = true;
				}
			}

			return;
		}
	}

	this->inDoor = false;
}

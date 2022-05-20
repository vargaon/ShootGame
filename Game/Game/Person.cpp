#include "Person.hpp"

bool Person::inRoom(const Room& r) const
{
	auto ob = r.outerBounds;
	return this->bounds.isIn(ob);
}

void Person::moveInRoom(const Room& r)
{
	auto ib = r.innerBounds;

	if (!this->bounds.isIn(ib)) {

		if (this->bounds.left < ib.left) {
			this->x = ib.left + this->size;
		}

		if (this->bounds.right > ib.right) {
			this->x = ib.right - this->size;
		}

		if (this->bounds.top < ib.top) {
			this->y = ib.top + this->size;
		}

		if (bounds.bot > ib.bot) {
			this->y = ib.bot - this->size;
		}

		Position p(this->x, this->y);
		this->setPosition(p);
	}
}

void Person::moveInRooms(rooms_con_t& rooms)
{
	if (this->room != nullptr) {
		this->moveInRoom(*this->room);
	}
	else {
		for (auto&& r : rooms) {

			if (this->inRoom(r)) {

				this->room = &r;
				this->moveInRoom(*this->room);
				break;
			}
		}
	}
}

void Person::moveInDoors(const doors_con_t& doors)
{
	for (auto&& d : doors) {

		auto db = d.bounds;

		if (this->bounds.inCollisionWith(db)) {

			if (this->inDoor) {

				if (!this->bounds.inRange(d.isHorizontal(), db)) {

					if (d.isHorizontal()) {

						if (this->bounds.left < db.left) {
							this->x = db.left + this->size;
						}

						if (this->bounds.right > db.right) {
							this->x = db.right - this->size;
						}
					}
					else {

						if (this->bounds.top < db.top) {
							this->y = db.top + this->size;
						}

						if (this->bounds.bot > db.bot) {
							this->y = db.bot - this->size;
						}
					}

					Position p(this->x, this->y);
					this->setPosition(p);
				}
			}

			else {
				if (this->bounds.inRange(d.isHorizontal(), db)) {
					this->inDoor = true;
					this->room = nullptr;
				}
			}

			return;
		}
	}

	this->inDoor = false;
}

void Person::setMovePower(PersonMovePower mp)
{
	this->movePower = mp;
}

void Person::setDirectionByPosition(Position& p)
{
	this->setDirection(atan2(p.y - this->y, p.x - this->x) * 180 / float(PI));
}

void Person::setStartPositionByRoom(Room* pRoom)
{
	this->room = pRoom;
	auto p = pRoom->getCentrePosition();

	this->x = p.x;
	this->y = p.y;

	this->setPosition(p);
}

const Room* Person::getRoom() const
{
	return this->room;
}

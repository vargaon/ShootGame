#include "Person.hpp"

void Person::moveInRooms(rooms_con_t& rooms, Bounds& bounds)
{
	for (auto&& r : rooms) {
		auto ob = r.outerBounds;

		if (bounds.isIn(ob)) {
			auto ib = r.innerBounds;

			if (!bounds.isIn(ib)) {

				if (bounds.left < ib.left) {
					this->x = ib.left + this->size;
				}

				if (bounds.right > ib.right) {
					this->x = ib.right - this->size;
				}

				if (bounds.top < ib.top) {
					this->y = ib.top + this->size;
				}

				if (bounds.bot > ib.bot) {
					this->y = ib.bot - this->size;
				}
			}

			break;
		}
	}
}

void Person::moveInDoors(doors_con_t& doors, Bounds& bounds)
{
	for (auto&& d : doors) {

		auto db = d.bounds;

		if (bounds.inCollisionWith(db)) {

			if (this->inDoor) {

				if (!bounds.inRange(d.isHorizontal(), db)) {

					if (d.isHorizontal()) {

						if (bounds.left < db.left) {
							this->x = db.left + this->size;
						}

						if (bounds.right > db.right) {
							this->x = db.right - this->size;
						}
					}
					else {

						if (bounds.top < db.top) {
							this->y = db.top + this->size;
						}

						if (bounds.bot > db.bot) {
							this->y = db.bot - this->size;
						}
					}
				}
			}

			else {
				this->inDoor = bounds.inRange(d.isHorizontal(), db);
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

void Person::setDirectionByPosition(float x, float y)
{
	this->setDirection(atan2(y - this->y, x - this->x) * 180 / float(PI));
}

#include "Bullet.hpp"

using namespace sf;

Bullet::Bullet(sf::Vector2f position, int angle): Entity(2.f, 30, Color::Black, position, angle), active(true)
{
	auto p_directions = computeDirectionsPowers();

	this->dx = p_directions.x;
	this->dy = p_directions.y;

}

void Bullet::Update(sf::Vector2u winSize, doors_con_t& doors)
{
	if (!this->active) return;

	this->x += this->dx * 4;
	this->y += this->dy * 4;

	bool skip_wall = false;

	auto b_bounds = FloatRect(this->x, this->y, this->size * 2, this->size * 2);

	/*
	* 
	for (auto&& d : doors) {
		auto d_bounds = d.getGlobalBounds();

		if (b_bounds.intersects(d_bounds)) {
			skip_wall = true;
			break;
		}
	}

	*/

	/*

	if (!skip_wall) {
		for (auto&& w : walls) {
			auto w_bounds = w.getGlobalBounds();

			if (b_bounds.intersects(w_bounds)) {
				this->active = false;
				return;
			}
		}
	}

	*/
	

	if (this->x > winSize.x || this->x < 0 || this->y > winSize.y || this->y < 0) this->active = false;
}

void Bullet::Render(sf::RenderWindow& window)
{
	this->entity.setPosition(Vector2f(this->x, this->y));
	window.draw(this->entity);
}

bool Bullet::isNotActive()
{
	return !this->active;
}

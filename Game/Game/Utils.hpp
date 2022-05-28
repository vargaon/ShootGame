#pragma once

class Float2Vector {

public:
	float x = 0.f;
	float y = 0.f;

	Float2Vector() {};
	Float2Vector(float x, float y) : x(x), y(y) {};

	virtual ~Float2Vector() {};
};

class Position : public Float2Vector {

public:
	Position() {};
	Position(float x, float y) : Float2Vector(x, y) {};
};

class Bounds {

public:

	Bounds() {};
	Bounds(float width, float height, Position p);
	Bounds(float width, float height) : Bounds(width, height, { 0.f, 0.f }) {};

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBot() const;

	bool isIn(const Bounds& b) const;
	bool inCollisionWith(const Bounds& b) const;
	bool inRange(bool horizontal, const Bounds& b) const;
	bool contains(const Float2Vector& v) const;

	void updateByPosition(Position p);

private:

	float top = 0.f;
	float bot = 0.f;
	float left = 0.f;
	float right = 0.f;

	float width = 0.f;
	float height = 0.f;
};
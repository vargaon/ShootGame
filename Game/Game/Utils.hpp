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

	float top = 0.f;
	float bot = 0.f;
	float left = 0.f;
	float right = 0.f;

	Bounds() {};
	Bounds(float top, float bot, float left, float right) : top(top), bot(bot), left(left), right(right) {};

	bool inCollisionWith(Bounds& b);
	bool isIn(Bounds& b);
	bool inRange(bool horizontal, Bounds& b);
	bool contains(Float2Vector& v);
};
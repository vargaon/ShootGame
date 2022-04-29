#pragma once

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
};

class Position {
public:
	float x = 0.f;
	float y = 0.f;

	Position() {};
	Position(float x, float y) : x(x), y(y) {};
};
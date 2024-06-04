#pragma once

#include <math.h>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <Math/Constants.hpp>
using namespace std;


struct Vec2d {
	float x; float y;

	Vec2d();
	Vec2d(float x_value, float y_value);
	Vec2d normalise();
	double size();
	Vec2d rotate90degrees(bool rightSide = true);
	// Rotate around the center in the axis defined (0 for x, 1 for y and 2 for z)
	Vec2d rotate(float radians);
	bool is_right_side(Vec2d vec, Vec2d pos);
	double scalar(Vec2d other);
	bool operator==(Vec2d const& other);
	bool operator!=(Vec2d const& other);
	bool alm_equal(Vec2d other);

	string to_str();

	Vec2d add(Vec2d other);
	Vec2d sub(Vec2d other);
	Vec2d mul(float n);
	Vec2d div(float n);
	Vec2d operator+(Vec2d other) { return add(other); }
	Vec2d operator+() { return *this; }
	Vec2d operator-(Vec2d other) { return sub(other); }
	Vec2d operator-() { return { -x, -y }; }
	Vec2d operator*(float other) { return mul(other); }
	Vec2d operator/(float other) { return div(other); }
};


float dist(Vec2d p1, Vec2d p2);

Vec2d vec(float x, float y);

ostream& operator<<(ostream& out, Vec2d v);
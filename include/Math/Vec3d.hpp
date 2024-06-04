#pragma once

#include <math.h>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <Math/Constants.hpp>
using namespace std;



struct Vec3d {
	float x; float y; float z;

	Vec3d();
	Vec3d(float x_value, float y_value, float z_value);
	Vec3d normalise();
	double size();
	double scalar(Vec3d other);
	Vec3d normal(Vec3d other);
	Vec3d rotate(float radians, int axis);
	Vec3d rotate(float radians, int axis, Vec3d center);
	bool operator==(Vec3d const& other);
	bool operator!=(Vec3d const& other);
	bool alm_equal(Vec3d other);
	int hash();

	string to_str();

	Vec3d add(Vec3d other);
	Vec3d sub(Vec3d other);
	Vec3d mul(float n);
	Vec3d div(float n);
	Vec3d operator+(Vec3d other) { return add(other); }
	Vec3d operator+() { return *this; }
	Vec3d operator-(Vec3d other) { return sub(other); }
	Vec3d operator-() { return { -x, -y, -z }; }
	Vec3d operator*(float other) { return mul(other); }
	Vec3d operator/(float other) { return div(other); }
};


float dist(Vec3d p1, Vec3d p2);

Vec3d vec(float x, float y, float z);

ostream& operator<<(ostream& out, Vec3d v);
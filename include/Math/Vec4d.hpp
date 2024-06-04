#pragma once

#include <math.h>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <Math/Constants.hpp>
using namespace std;



struct Vec4d {
	float x; float y; float z; float w;

	Vec4d();
	Vec4d(float x_value, float y_value, float z_value, float w_value);
	Vec4d normalise() const;
	double size() const;
	double scalar(Vec4d other) const;
	bool operator==(Vec4d const& other) const;
	bool operator!=(Vec4d const& other) const;
	bool alm_equal(Vec4d other) const;
	Vec4d rotation(float radians, int axis1, int axis2) const;
	Vec4d rotation(float radians, int axis1, int axis2, Vec4d center) const;
	// radians doit etre un tableau avec les 6 angles (xy, xz, xw, yz, yw, zw)
	Vec4d rotation(float* radians) const;
	int hash() const;

	string to_str() const;

	Vec4d add(Vec4d other) const;
	Vec4d sub(Vec4d other) const;
	Vec4d mul(float n) const;
	Vec4d div(float n) const;
	Vec4d operator+(Vec4d other) const { return add(other); }
	Vec4d operator+() const { return *this; }
	Vec4d operator-(Vec4d other) const { return sub(other); }
	Vec4d operator-() const { return { -x, -y, -z, -w }; }
	Vec4d operator*(float other) const { return mul(other); }
	Vec4d operator/(float other) const { return div(other); }
};


float dist(Vec4d p1, Vec4d p2);

Vec4d vec(float x, float y, float z, float w);

ostream& operator<<(ostream& out, Vec4d v);
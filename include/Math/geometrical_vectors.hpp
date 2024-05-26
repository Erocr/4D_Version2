#ifndef VECTORS
#define VECTORS

#include <math.h>
#include <string>
#include <stdexcept>
using namespace std;


const double PI = 3.141592653589;

struct Vec2d {
	float x; float y;

	Vec2d();
	Vec2d(float x_value, float y_value);
	Vec2d normalise();
	double size();
	Vec2d rotate90degrees(bool rightSide=true);
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
	string to_str();
	int hash();

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
	string to_str() const;
	Vec4d rotation(float radians, int axis1, int axis2) const;
	Vec4d rotation(float radians, int axis1, int axis2, Vec4d center) const;
	// radians doit etre un tableau avec les 6 angles (xy, xz, xw, yz, yw, zw)
	Vec4d rotation(float* radians) const;
	int hash() const;

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


float dist(Vec2d p1, Vec2d p2);
float dist(Vec3d p1, Vec3d p2);
float dist(Vec4d p1, Vec4d p2);

Vec2d vec(float x, float y);
Vec3d vec(float x, float y, float z);
Vec4d vec(float x, float y, float z, float w);

ostream& operator<<(ostream& out, Vec2d v);
ostream& operator<<(ostream& out, Vec3d v);
ostream& operator<<(ostream& out, Vec4d v);

#endif
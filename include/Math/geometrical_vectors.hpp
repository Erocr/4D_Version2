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
	Vec2d add(Vec2d other);
	Vec2d sub(Vec2d other);
	Vec2d mul(float n);
	Vec2d div(float n);
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
};

struct Vec3d {
	float x; float y; float z;

	Vec3d();
	Vec3d(float x_value, float y_value, float z_value);
	Vec3d add(Vec3d other);
	Vec3d sub(Vec3d other);
	Vec3d mul(float n);
	Vec3d div(float n);
	Vec3d normalise();
	double size();
	double scalar(Vec3d other);
	Vec3d normal(Vec3d other);
	Vec3d rotate(float radians, int axis, Vec3d center=Vec3d(0, 0, 0));
	bool operator==(Vec3d const& other);
	bool operator!=(Vec3d const& other);
	bool alm_equal(Vec3d other);
	string to_str();
	int hash();
};

struct Vec4d {
	float x; float y; float z; float w;

	Vec4d();
	Vec4d(float x_value, float y_value, float z_value, float w_value);
	Vec4d add(Vec4d other);
	Vec4d sub(Vec4d other);
	Vec4d mul(float n);
	Vec4d div(float n);
	Vec4d normalise();
	double size();
	double scalar(Vec4d other);
	bool operator==(Vec4d const& other);
	bool operator!=(Vec4d const& other);
	bool alm_equal(Vec4d other);
	string to_str();
};


Vec2d vec(int x, int y);
Vec3d vec(int x, int y, int z);
Vec4d vec(int x, int y, int z, int w);

#endif
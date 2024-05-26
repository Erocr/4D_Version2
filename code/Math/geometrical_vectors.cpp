#pragma once

#include "Math/geometrical_vectors.hpp"
#include <cmath>

#ifndef DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

Vec2d::Vec2d() { x = 0; y = 0; }
Vec2d::Vec2d(float x_value, float y_value) { x = x_value; y = y_value; }
Vec2d Vec2d::add(Vec2d other) { return Vec2d(other.x + x, other.y + y); }
Vec2d Vec2d::sub(Vec2d other) { return Vec2d(x - other.x, y - other.y); }
Vec2d Vec2d::mul(float n) { return Vec2d(x * n, y * n); }
Vec2d Vec2d::div(float n) { 
	if (n == 0) throw runtime_error("division by zero");
	return Vec2d(x / n, y / n); 
}
Vec2d Vec2d::normalise() { return div(size()); }
double Vec2d::size() { return sqrt(x * x + y * y); }
Vec2d Vec2d::rotate90degrees(bool rightSide) {
	if (rightSide) {
		return Vec2d(-y, x);
	}
	else {
		return Vec2d(y, -x);
	}
}
Vec2d Vec2d::rotate(float radians) { return Vec2d(cos(radians) * x - sin(radians) * y, sin(radians) * x + cos(radians) * y); }
double Vec2d::scalar(Vec2d other) { return other.x * x + other.y * y; }
bool Vec2d::is_right_side(Vec2d vec, Vec2d pos) {
	Vec2d v1 = Vec2d(vec.x, vec.y).rotate90degrees();
	Vec2d v2(pos.x - x, pos.y - y);
	return v1.scalar(v2) > 0;
}
bool Vec2d::operator==(Vec2d const& other) { return x == other.x && y == other.y; }
bool Vec2d::operator!=(Vec2d const& other) { return x != other.x || y != other.y; }
bool Vec2d::alm_equal(Vec2d other) { return abs(x - other.x) < 0.001 && abs(y - other.y) < 0.001; }
string Vec2d::to_str() { return to_string(x) + ", " + to_string(y); }





Vec3d::Vec3d() { x = 0; y = 0; z = 0; }
Vec3d::Vec3d(float x_value, float y_value, float z_value) { x = x_value; y = y_value; z = z_value; }
Vec3d Vec3d::add(Vec3d other) { return Vec3d(x + other.x, y + other.y, z + other.z); }
Vec3d Vec3d::sub(Vec3d other) { return Vec3d(x - other.x, y - other.y, z - other.z); }
Vec3d Vec3d::mul(float n) { return Vec3d(x * n, y * n, z * n); }
Vec3d Vec3d::div(float n) { 
	if (n == 0) throw runtime_error("division by 0");
	return Vec3d(x / n, y / n, z / n); }
Vec3d Vec3d::normalise() { return div(size()); }
double Vec3d::size() { return sqrt(x * x + y * y + z * z); }
double Vec3d::scalar(Vec3d other) { return x * other.x + y * other.y + z * other.z; }
Vec3d Vec3d::normal(Vec3d other) {
	return Vec3d(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}


Vec3d Vec3d::rotate(float radians, int axis) {
	if (axis == 0) {
		return Vec3d(x, y * cos(radians) + z * sin(radians), -y * sin(radians) + z * cos(radians));
	}
	else if (axis == 1) {
		return Vec3d(x * cos(radians) + z * sin(radians), y, -x * sin(radians) + z * cos(radians));
	}
	else {
		return Vec3d(x * cos(radians) - y * sin(radians), x * sin(radians) + y * cos(radians), z);
	}
}


Vec3d Vec3d::rotate(float radians, int axis, Vec3d center) {
	Vec3d v = this->sub(center);
	return v.rotate(radians, axis);
}


bool Vec3d::operator==(Vec3d const& other) { return x == other.x && y == other.y && z == other.z; };
bool Vec3d::operator!=(Vec3d const& other) { return x != other.x || y != other.y || z != other.z; };
bool Vec3d::alm_equal(Vec3d other) {
	return abs(x - other.x) < 0.001 && abs(y - other.y) < 0.001 && abs(z - other.z) < 0.001;
}
string Vec3d::to_str() { return to_string(x) + ", " + to_string(y) + ", " + to_string(z); }
int Vec3d::hash() { return int(x + y + z)%100; }


Vec3d normal(Vec3d v1, Vec3d v2) { 
	return Vec3d(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); 
}





Vec4d::Vec4d() { x = 0; y = 0; z = 0; w = 0; };
Vec4d::Vec4d(float x_value, float y_value, float z_value, float w_value) {
	x = x_value; y = y_value; z = z_value; w = w_value;
}
Vec4d Vec4d::add(Vec4d other) const { return Vec4d(x + other.x, y + other.y, z + other.z, w + other.w); }
Vec4d Vec4d::sub(Vec4d other) const { return Vec4d(x - other.x, y - other.y, z - other.z, w - other.w); }
Vec4d Vec4d::mul(float n) const { return Vec4d(x * n, y * n, z * n, w * n); }
Vec4d Vec4d::div(float n) const { 
	if (n == 0) throw runtime_error("division by 0");
	return Vec4d(x / n, y / n, z / n, w / n); }
Vec4d Vec4d::normalise() const { return div(size()); }
double Vec4d::size() const { return sqrt(x * x + y * y + z * z + w * w); }
double Vec4d::scalar(Vec4d other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
bool Vec4d::operator==(Vec4d const& other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}
bool Vec4d::operator!=(Vec4d const& other) const {
	return x != other.x || y != other.y || z != other.z || w != other.w;
}
bool Vec4d::alm_equal(Vec4d other) const {
	return abs(x - other.x) < 0.001 && abs(y - other.y) < 0.001 && abs(z - other.z) < 0.001 && abs(w - other.w) < 0.001;
}
string Vec4d::to_str() const { return to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(z); }


Vec4d Vec4d::rotation(float radians, int axis1, int axis2) const {
	if (axis2 > axis1) swap(axis1, axis2);
	if (axis1 == 0 && axis2 == 1) 
		return { x * cos(radians) + y * sin(radians),
				-x * sin(radians) + y * cos(radians),
				z,
				w };
	if (axis1 == 1 && axis2 == 2)
		return { x,
				 y * cos(radians) + z * sin(radians),
				 -y * sin(radians) + z * cos(radians),
				w };
	if (axis1 == 0 && axis2 == 2)
		return { x * cos(radians) - z * sin(radians),
				 y,
				 x * sin(radians) + z * cos(radians),
				 w};
	if (axis1 == 0 && axis2 == 3)
		return { x * cos(radians) + w * sin(radians),
				 y,
				 z,
				 -x * cos(radians) + w * cos(radians) };
	if (axis1 == 1 && axis2 == 3)
		return { x,
				 y * cos(radians) - w * sin(radians),
				 z,
				 y * sin(radians) + w * cos(radians) };
	if (axis1 == 2 && axis2 == 3)
		return { x,
				 y,
				 z * cos(radians) - w * sin(radians),
				 z * sin(radians) + w * cos(radians) };
}

Vec4d Vec4d::rotation(float radians, int axis1, int axis2, Vec4d center) const {
	return (*this - center).rotation(radians, axis1, axis2) + center;
}


Vec4d Vec4d::rotation(float* angles) const {
	Vec4d res = rotation(angles[0], 0, 1);
	res = res.rotation(angles[1], 0, 2);
	res = res.rotation(angles[2], 0, 3);
	res = res.rotation(angles[3], 1, 2);
	res = res.rotation(angles[4], 1, 3);
	res = res.rotation(angles[5], 2, 3);
	return res;
}


float dist(Vec2d p1, Vec2d p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float dist(Vec3d p1, Vec3d p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

float dist(Vec4d p1, Vec4d p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2) + pow(p1.w - p2.w, 2));
}


Vec2d vec(float x, float y) { return Vec2d(x, y); }
Vec3d vec(float x, float y, float z) { return Vec3d(x, y, z); }
Vec4d vec(float x, float y, float z, float w) { return Vec4d(x, y, z, w); }


ostream& operator<<(ostream& out, Vec2d v) {
	out << '(' << v.x << ", " << v.y << ')';
	return out;
}

ostream& operator<<(ostream& out, Vec3d v) {
	out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return out;
}

ostream& operator<<(ostream& out, Vec4d v) {
	out << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
	return out;
}


TEST_CASE("vectors 2d") {
	Vec2d p1;
	Vec2d v1 = vec(1, 0);
	Vec2d p2 = vec(1, 1);
	Vec2d v2(3, 4);
	SUBCASE("constructor") {
		CHECK(p1.x == 0);
		CHECK(p1.y == 0);
		CHECK(v2.x == 3);
		CHECK(v2.y == 4);
	}
	SUBCASE("vec function") {
		CHECK(v1.x == 1);
		CHECK(v1.y == 0);
		CHECK(p2.x == 1);
		CHECK(p2.y == 1);
	}
	SUBCASE("operator==") {
		CHECK((Vec2d(0, 0) == Vec2d(0, 0)));
		CHECK_FALSE((Vec2d(1, 0) == Vec2d(0, 1)));
		CHECK((Vec2d(1, 0) != Vec2d(0, 1)));
		CHECK_FALSE((Vec2d(0, 0) != Vec2d(0, 0)));
		CHECK((Vec2d(0, 0).alm_equal(Vec2d(0, 0))));
		CHECK((Vec2d(0.0001, 0).alm_equal(Vec2d(0, 0))));
		CHECK_FALSE((Vec2d(1, 0).alm_equal(Vec2d(0, 1))));
	}
	SUBCASE("add") {
		CHECK((Vec2d(10, 10).add(Vec2d(10, 10)) == Vec2d(20, 20)));
		CHECK((p1.add(v1) == v1));
	}
	SUBCASE("sub") {
		CHECK((Vec2d(10, 10).sub(Vec2d(10, 10)) == Vec2d(0, 0)));
		CHECK((v1.sub(p1) == v1));
	}
	SUBCASE("mul") {
		CHECK((Vec2d(1, 2).mul(10) == Vec2d(10, 20)));
		CHECK((v1.mul(0) == p1));
	}
	SUBCASE("div") {
		CHECK((v1.div(1) == v1));
		CHECK((Vec2d(2, 2).div(2) == Vec2d(1, 1)));
		CHECK_THROWS_AS(v1.div(0), runtime_error);
	}
	SUBCASE("normalise") {
		CHECK((Vec2d(1, 0).normalise() == Vec2d(1, 0)));
		CHECK((Vec2d(10, 0).normalise() == Vec2d(1, 0)));
		CHECK_THROWS_AS(Vec2d(0, 0).normalise(), runtime_error);
	}
	SUBCASE("size") {
		CHECK(v1.size() == 1.0);
		CHECK(Vec2d(3, 4).size() == 5.0);
		CHECK(Vec2d(-3, -4).size() == 5.0);
	}
	SUBCASE("rotate90degrees") {
		CHECK((v1.rotate90degrees() == Vec2d(0, 1)));
		CHECK((v2.rotate90degrees().rotate90degrees().rotate90degrees().rotate90degrees() == v2));
		CHECK((Vec2d(1, 1).rotate90degrees() == Vec2d(-1, 1)));
	}
	SUBCASE("rotate") {
		CHECK((v1.rotate(PI / 2).alm_equal(Vec2d(0, 1))));
		CHECK((Vec2d(56, 89).rotate(PI / 2).alm_equal(Vec2d(56, 89).rotate90degrees())));
	}
	SUBCASE("scalar") {
		CHECK(v1.scalar(v2) == 3.0);
		CHECK(Vec2d(0, 0).scalar(v1) == 0.0);
		CHECK(Vec2d(0, 0).scalar(v2) == 0.0);
		CHECK(Vec2d(5, 5).scalar(Vec2d(1, 1)) == 10.0);
	}
	SUBCASE("is_right_side") {
		CHECK(p1.is_right_side(v1, p2));
		CHECK_FALSE(p1.is_right_side(v1, Vec2d(-1, 0)));
	}
};


TEST_CASE("vectors 3d") {
	Vec3d p1;
	Vec3d v1 = vec(1, 0, 0);
	Vec3d p2 = vec(1, 1, 1);
	Vec3d v2(3, 4, 5);
	SUBCASE("constructor") {
		CHECK(p1.x == 0);
		CHECK(p1.y == 0);
		CHECK(p1.z == 0);
		CHECK(v2.x == 3);
		CHECK(v2.y == 4);
		CHECK(v2.z == 5);
	}
	SUBCASE("vec function") {
		CHECK(v1.x == 1);
		CHECK(v1.y == 0);
		CHECK(v1.z == 0);
		CHECK(p2.x == 1);
		CHECK(p2.y == 1);
		CHECK(p2.z == 1);
	}
	SUBCASE("operator==") {
		CHECK((Vec3d(0, 0, 0) == Vec3d()));
		CHECK_FALSE((Vec3d(1, 0, 0) == Vec3d(0, 1, 1)));
		CHECK((Vec3d(1, 0, 1) != Vec3d(0, 1, 1)));
		CHECK_FALSE((Vec3d() != Vec3d(0, 0, 0)));
		CHECK((Vec3d(0, 0, 0).alm_equal(Vec3d(0, 0, 0))));
		CHECK((Vec3d(0.0001, 0, 0).alm_equal(Vec3d(0, 0, 0))));
		CHECK_FALSE((Vec3d(1, 0, 0).alm_equal(Vec3d(0, 1, 1))));
	}
	SUBCASE("add") {
		CHECK((vec(10, 10, 5).add(vec(10, 10, 6)) == vec(20, 20, 11)));
		CHECK((p1.add(v1) == v1));
	}
	SUBCASE("sub") {
		CHECK((Vec3d(10, 10, 10).sub(Vec3d(10, 10, 10)) == Vec3d(0, 0, 0)));
		CHECK((v1.sub(p1) == v1));
	}
	SUBCASE("mul") {
		CHECK((Vec3d(1, 2, 3).mul(10) == Vec3d(10, 20, 30)));
		CHECK((v1.mul(0) == p1));
	}
	SUBCASE("div") {
		CHECK((v1.div(1) == v1));
		CHECK((vec(2, 2, 4).div(2) == vec(1, 1, 2)));
		CHECK_THROWS_AS(v1.div(0), runtime_error);
	}
	SUBCASE("normalise") {
		CHECK((v1.normalise() == v1));
		CHECK((Vec3d(10, 0, 0).normalise() == Vec3d(1, 0, 0)));
		CHECK_THROWS_AS(Vec3d().normalise(), runtime_error);
	}
	SUBCASE("size") {
		CHECK(v1.size() == 1.0);
		CHECK(Vec3d(2, 3, 6).size() == 7.0);
		CHECK(Vec3d(-2, -3, -6).size() == 7.0);
	}
	SUBCASE("rotate") {
		CHECK((v1.rotate(PI / 2, 2).alm_equal(Vec3d(0, 1, 0))));
		CHECK((v1.rotate(PI / 2, 1).alm_equal(Vec3d(0, 0, -1))));
		CHECK((v1.rotate(PI / 2, 0).alm_equal(Vec3d(1, 0, 0))));
	}
	SUBCASE("scalar") {
		CHECK(v1.scalar(v2) == 3.0);
		CHECK(Vec3d(0, 0, 0).scalar(v1) == 0.0);
		CHECK(Vec3d(0, 0, 0).scalar(v2) == 0.0);
		CHECK(Vec3d(5, 5, 5).scalar(Vec3d(1, 1, 1)) == 15.0);
	}
	SUBCASE("hash") {
		Vec3d v = vec(1000, 1000, 61735);
		CHECK(v.hash() < 100);
		CHECK(v.hash() >= 0);
	}
	SUBCASE("normal") {
		CHECK((vec(1, 0, 0).normal(vec(0, 1, 0)) == Vec3d(0, 0, 1)));
	}
};

TEST_CASE("vectors 4d") {
	Vec4d p1;
	Vec4d v1 = vec(1, 0, 0, 0);
	Vec4d p2 = vec(1, 1, 1, 1);
	Vec4d v2(3, 4, 5, 6);
	SUBCASE("constructor") {
		CHECK(p1.x == 0);
		CHECK(p1.y == 0);
		CHECK(p1.z == 0);
		CHECK(p1.w == 0);
		CHECK(v2.x == 3);
		CHECK(v2.y == 4);
		CHECK(v2.z == 5);
		CHECK(v2.w == 6);
	}
	SUBCASE("vec function") {
		CHECK(v1.x == 1);
		CHECK(v1.y == 0);
		CHECK(v1.z == 0);
		CHECK(v1.w == 0);
		CHECK(p2.x == 1);
		CHECK(p2.y == 1);
		CHECK(p2.z == 1);
		CHECK(p2.w == 1);
	}
	SUBCASE("operator==") {
		CHECK((Vec4d(0, 0, 0, 0) == Vec4d()));
		CHECK_FALSE((Vec4d(1, 0, 0, 0) == Vec4d(0, 1, 1, 0)));
		CHECK((Vec4d(1, 0, 1, 0) != Vec4d(0, 1, 1, 0)));
		CHECK_FALSE((Vec4d() != Vec4d(0, 0, 0, 0)));
		CHECK((Vec4d(0, 0, 0, 0).alm_equal(Vec4d(0, 0, 0, 0))));
		CHECK((Vec4d(0.0001, 0, 0, 0.0001).alm_equal(Vec4d())));
		CHECK_FALSE((Vec4d(1, 0, 1, 1).alm_equal(Vec4d(0, 1, 1, 0))));
	}
	SUBCASE("add") {
		CHECK((vec(10, 10, 5, 8).add(vec(10, 10, 6, 2)) == vec(20, 20, 11, 10)));
		CHECK((p1.add(v1) == v1));
	}
	SUBCASE("sub") {
		CHECK((Vec4d(10, 10, 10, 5).sub(Vec4d(10, 10, 10, 10)) == Vec4d(0, 0, 0, -5)));
		CHECK((v1.sub(p1) == v1));
	}
	SUBCASE("mul") {
		CHECK((Vec4d(1, 2, 3, 4).mul(10) == Vec4d(10, 20, 30, 40)));
		CHECK((v1.mul(0) == p1));
	}
	SUBCASE("div") {
		CHECK((v1.div(1) == v1));
		CHECK((vec(2, 2, 4, 8).div(2) == vec(1, 1, 2, 4)));
		CHECK_THROWS_AS(v1.div(0), runtime_error);
	}
	SUBCASE("normalise") {
		CHECK((v1.normalise() == v1));
		CHECK((Vec4d(10, 0, 0, 0).normalise() == Vec4d(1, 0, 0, 0)));
		CHECK_THROWS_AS(Vec4d(0, 0, 0, 0).normalise(), runtime_error);
	}
	SUBCASE("size") {
		CHECK(v1.size() == 1.0);
		CHECK(Vec4d(2, 4, 5, 6).size() == 9.0);
		CHECK(Vec4d(-2, -4, -5, -6).size() == 9.0);
	}
	SUBCASE("scalar") {
		CHECK(v1.scalar(v2) == 3.0);
		CHECK(Vec4d().scalar(v1) == 0.0);
		CHECK(Vec4d().scalar(v2) == 0.0);
		CHECK(Vec4d(5, 5, 5, 4).scalar(Vec4d(1, 1, 1, 1)) == 19.0);
	}
};

/*
	Line2d l1 = Line2d(Vec2d(0, 0), Vec2d(2, 0));
	Line2d l2 = Line2d(Vec2d(1, 1), Vec2d(1, -1));
	Line2d l3 = Line2d(Vec2d(0, 1), Vec2d(1, 1));
	CHECK(l1.intersection(l2) == Vec2d(1, 0));
	CHECK(l1.intersection(l3) == Vec2d()); */
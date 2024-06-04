#include <Math/Vec3d.hpp>

#include "doctest.h"


Vec3d::Vec3d() { x = 0; y = 0; z = 0; }

Vec3d::Vec3d(float x_value, float y_value, float z_value) { x = x_value; y = y_value; z = z_value; }

Vec3d Vec3d::add(Vec3d other) { return Vec3d(x + other.x, y + other.y, z + other.z); }

Vec3d Vec3d::sub(Vec3d other) { return Vec3d(x - other.x, y - other.y, z - other.z); }

Vec3d Vec3d::mul(float n) { return Vec3d(x * n, y * n, z * n); }

Vec3d Vec3d::div(float n) {
	if (n == 0) throw runtime_error("division by 0");
	return Vec3d(x / n, y / n, z / n);
}

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

int Vec3d::hash() { return abs(int(x + y + z) % 100); }

Vec3d normal(Vec3d v1, Vec3d v2) {
	return Vec3d(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}



float dist(Vec3d p1, Vec3d p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

Vec3d vec(float x, float y, float z) { return Vec3d(x, y, z); }

ostream& operator<<(ostream& out, Vec3d v) {
	out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return out;
}




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
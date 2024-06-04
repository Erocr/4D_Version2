#include <Math/Vec4d.hpp>

#include "doctest.h"


Vec4d::Vec4d() { x = 0; y = 0; z = 0; w = 0; };

Vec4d::Vec4d(float x_value, float y_value, float z_value, float w_value) {
	x = x_value; y = y_value; z = z_value; w = w_value;
}

Vec4d Vec4d::add(Vec4d other) const { return Vec4d(x + other.x, y + other.y, z + other.z, w + other.w); }

Vec4d Vec4d::sub(Vec4d other) const { return Vec4d(x - other.x, y - other.y, z - other.z, w - other.w); }

Vec4d Vec4d::mul(float n) const { return Vec4d(x * n, y * n, z * n, w * n); }

Vec4d Vec4d::div(float n) const {
	if (n == 0) throw runtime_error("division by 0");
	return Vec4d(x / n, y / n, z / n, w / n);
}

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
	if (axis1 > axis2) swap(axis1, axis2);
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
				 w };
	if (axis1 == 0 && axis2 == 3)
		return { x * cos(radians) + w * sin(radians),
				 y,
				 z,
				 -x * sin(radians) + w * cos(radians) };
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
	throw runtime_error("impossible de faire une rotation sur ces axes");
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




float dist(Vec4d p1, Vec4d p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2) + pow(p1.w - p2.w, 2));
}

Vec4d vec(float x, float y, float z, float w) { return Vec4d(x, y, z, w); }

ostream& operator<<(ostream& out, Vec4d v) {
	out << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
	return out;
}





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
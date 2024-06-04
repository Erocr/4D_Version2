#include <Math/Vec2d.hpp>

#include <doctest.h>


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



float dist(Vec2d p1, Vec2d p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Vec2d vec(float x, float y) { return Vec2d(x, y); }

ostream& operator<<(ostream& out, Vec2d v) {
	out << '(' << v.x << ", " << v.y << ')';
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
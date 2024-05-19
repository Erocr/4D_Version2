#include "Math/geometrical_line.hpp"

#include "doctest.h"

Line2d::Line2d() {
	p1 = Vec2d();
	p2 = Vec2d();
	normal = Vec2d();
}
Line2d::Line2d(Vec2d p1, Vec2d p2) {
	this->p1 = p1; this->p2 = p2; normal = p2.sub(p1).rotate90degrees();
}
Line2d::Line2d(Vec2d p1, Vec2d p2, Vec2d normal) {
	this->p1 = p1; this->p2 = p2; this->normal = normal;
}
bool Line2d::in_normal_side(Vec2d p) {
	return p.sub(p1).scalar(normal) > 0;
}
Vec2d Line2d::intersection(Line2d other) {
	float x1 = p1.x; float x2 = p2.x; float x3 = other.p1.x; float x4 = other.p2.x;
	float y1 = p1.y; float y2 = p2.y; float y3 = other.p1.y; float y4 = other.p2.y;
	float denom = float(x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denom == 0) {
		throw runtime_error("no_intersections");
	}
	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
	return p1.add(p2.sub(p1).mul(t));
}

Line3d::Line3d() {
	p1 = Vec3d(0, 0, 0);
	p2 = Vec3d(1, 0, 0);
	dir = Vec3d(1, 0, 0);
}
Line3d::Line3d(Vec3d point1, Vec3d point2) {
	p1 = point1;
	p2 = point2;
	dir = p2.sub(p1);
}
Vec3d Line3d::normal(Line3d other) {
	return dir.normal(other.dir);
}



Line4d::Line4d() {
	p1 = Vec4d(0, 0, 0, 0);
	p2 = Vec4d(1, 0, 0, 0);
	dir = Vec4d(1, 0, 0, 0);
}
Line4d::Line4d(Vec4d point1, Vec4d point2) {
	p1 = point1;
	p2 = point2;
	dir = p2.sub(p1);
}


TEST_CASE("Line2d") {
	Line2d l1 = Line2d();
	Line2d l2 = Line2d(Vec2d(0, 0), Vec2d(1, 0));
	Line2d l3 = Line2d(vec(10, 0), Vec2d(6, 8));
	SUBCASE("consturctor") {
		CHECK((l1.p1 == Vec2d()));
		CHECK((l1.p2 == Vec2d()));
		CHECK((l1.normal == Vec2d()));
		CHECK((l2.p1 == Vec2d(0, 0)));
		CHECK((l2.p2 == Vec2d(1, 0)));
		CHECK((l2.normal == Vec2d(0, 1)));
	}
	SUBCASE("in_normal_side") {
		CHECK((l2.in_normal_side(Vec2d(10, 1))));
		CHECK_FALSE((l2.in_normal_side(Vec2d(10, -1))));
	}
	SUBCASE("intersection") {
		CHECK((l2.intersection(l3) == Vec2d(10, 0)));
		CHECK_THROWS_AS(l2.intersection(Line2d(vec(0, 1), vec(1, 1))), runtime_error);
	}
};

TEST_CASE("Line3d") {
	Line3d l1(vec(0, 0, 0), vec(1, 0, 0));
	SUBCASE("constructor") {
		CHECK((l1.p1 == vec(0, 0, 0)));
		CHECK((l1.p2 == vec(1, 0, 0)));
		CHECK((l1.dir == vec(1, 0, 0)));
	}
}


TEST_CASE("Line4d") {
	Line4d l1(vec(0, 0, 0, 0), vec(1, 0, 0, 0));
	SUBCASE("constructor") {
		CHECK((l1.p1 == vec(0, 0, 0, 0)));
		CHECK((l1.p2 == vec(1, 0, 0, 0)));
		CHECK((l1.dir == vec(1, 0, 0, 0)));
	}
}
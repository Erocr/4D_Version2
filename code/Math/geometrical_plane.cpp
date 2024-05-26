#include "Math/geometrical_plane.hpp"

#include "doctest.h"

Plane3d::Plane3d(Vec3d p, Vec3d n) {
	point = p;
	normal = n;
}
void Plane3d::rotate(float radians, int axis) {
	normal = normal.rotate(radians, axis);
}
void Plane3d::move(Vec3d added_vector) {
	point = point + added_vector;
}

/** @return true if the point is in the side pointed by the normal vector **/
bool Plane3d::in_normal_side(Vec3d p) {
	return (p - point).scalar(normal) > 0;
}

/** @return Vec3d(0, 0, 0) if there is no intersections, else the point of intersection **/
Vec3d Plane3d::intersection(Line3d line) {
	if (line.dir.scalar(normal) == 0) {
		return Vec3d();
	}
	float k = ((point - line.p1).scalar(normal)) / (line.dir.scalar(normal));
	if (k < 0 || k > 1) {
		return Vec3d();
	}
	return line.p1 + (line.dir * k);
}


TEST_CASE("plane3d") {
	Plane3d p1 = Plane3d(vec(0, 0, 0), vec(0, 0, 1));
	SUBCASE("constructor") {
		CHECK((p1.point == vec(0, 0, 0)));
		CHECK((p1.normal == vec(0, 0, 1)));
	}
	SUBCASE("rotate") {
		p1.rotate(PI / 2, 0);
		CHECK((p1.point == vec(0, 0, 0)));
		CHECK((p1.normal.alm_equal(vec(0, 1, 0))));
	}
	SUBCASE("move") {
		p1.move(vec(1, 0, 0));
		CHECK((p1.point == vec(1, 0, 0)));
		p1.move(vec(1, 0, 1));
		CHECK((p1.point == vec(2, 0, 1)));
	}
	SUBCASE("in_normal_side") {
		CHECK(p1.in_normal_side(vec(0, 0, 1)));
		CHECK(p1.in_normal_side(vec(-15, 23, 13)));
		CHECK_FALSE(p1.in_normal_side(vec(-15, 23, -13)));
	}
	SUBCASE("intersection") {
		Line3d line1(vec(0, 0, 10), vec(0, 0, 1));
		Line3d line2(vec(0, 0, 0), vec(0, 0, 1));
		CHECK((p1.intersection(line1) == vec(0, 0, 0)));
		CHECK((p1.intersection(line2) == Vec3d()));
	}
}
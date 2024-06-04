#include "Math/triangle.hpp"
#include <array>
#include <iostream>

#include "doctest.h"

Triangle2d::Triangle2d() {
	l1 = Line2d(); l2 = Line2d(); l3 = Line2d(); d = 0;
}
Triangle2d::Triangle2d(Vec2d p1, Vec2d p2, Vec2d p3, float _d) {
	l1 = Line2d(p1, p2); l2 = Line2d(p2, p3); l3 = Line2d(p3, p1); 
	d = _d;
}
vector<Vec2d> Triangle2d::get_draw_points() {
	return { l1.p1, l2.p1, l3.p1 };
}
vector<Triangle2d> Triangle2d::remove_behind_line(Line2d line) {
	array<bool, 3> sides = { line.in_normal_side(l1.p1), line.in_normal_side(l2.p1), line.in_normal_side(l3.p1) };
	if (!sides[0] && !sides[1] && !sides[2]) {
		return {};
	}
	else if (sides[0] && sides[1] && sides[2]) {
		return {*this};
	}
	else if (sides[0] && !sides[1] && !sides[2]) {
		return { Triangle2d(l1.p1, line.intersection(l1), line.intersection(l3), d) };
	}
	else if (!sides[0] && sides[1] && !sides[2]) {
		return { Triangle2d(l2.p1, line.intersection(l1), line.intersection(l2), d) };
	}
	else if (!sides[0] && !sides[1] && sides[2]) {
		return { Triangle2d(l3.p1, line.intersection(l2), line.intersection(l3), d) };
	}
	else if (sides[0] && sides[1] && !sides[2]) {
		Vec2d inter = line.intersection(l3);
		return { Triangle2d(l1.p1, l2.p1, inter, d), Triangle2d(l2.p1, line.intersection(l2), inter, d) };
	}
	else if (!sides[0] && sides[1] && sides[2]) {
		Vec2d inter = line.intersection(l1);
		return { Triangle2d(l2.p1, l3.p1, inter, d),
				 Triangle2d(l3.p1, line.intersection(l3), inter, d) };
	}
	else {
		Vec2d inter = line.intersection(l2);
		return { Triangle2d(l3.p1, l1.p1, inter, d),
				 Triangle2d(l1.p1, line.intersection(l1), inter, d) };
	}
}
bool Triangle2d::operator==(Triangle2d o) {
	return l1.p1 == o.l1.p1 && l2.p1 == o.l2.p1 && l3.p1 == o.l3.p1;
}

float Triangle2d::getDist() {
	return d;
}


string Triangle2d::to_str() {
	return l1.p1.to_str() + "  --  " + l2.p1.to_str() + "  --  " + l3.p1.to_str();
}



TEST_CASE("triangle2d") {
	Triangle2d t1 = Triangle2d(vec(0, 0), vec(1, 1), vec(1, 0), 0);
	SUBCASE("constructor/draw_points") {
		vector<Vec2d> points = t1.get_draw_points();
		CHECK(points.size() == 3);
		CHECK((points[0] == vec(0, 0)));
		CHECK((points[1] == vec(1, 1)));
		CHECK((points[2] == vec(1, 0)));
	}
	SUBCASE("remove_behind_line") {
		CHECK(t1.remove_behind_line(Line2d(vec(2, 0), vec(2, 1), vec(1, 0))).size() == 0);  // first if
		CHECK(t1.remove_behind_line(Line2d(vec(2, 0), vec(2, 1), vec(-1, 0)))[0] == t1);  // second if
		vector<Triangle2d> t = t1.remove_behind_line(Line2d(vec(0.5, 0), vec(0.5, 1), vec(-1, 0)));
		CHECK(t.size() == 1);
		if (t.size() == 1) 
			CHECK(t[0] == Triangle2d(vec(0, 0), vec(0.5, 0.5), vec(0.5, 0), 0));
	}
}




Triangle3d::Triangle3d() {
	points_list = NULL;
	l1 = Line3d(); l2 = Line3d(); l3 = Line3d();
	p1_pos = PointReference(); p2_pos = PointReference(); p3_pos = PointReference();
}
Triangle3d::Triangle3d(Vec3d p1, Vec3d p2, Vec3d p3, PointsList* pointsList) {
	points_list = pointsList;
	l1 = Line3d(p1, p2);
	l2 = Line3d(p2, p3);
	l3 = Line3d(p3, p1);
	p1_pos = PointReference();
	p2_pos = PointReference();
	p3_pos = PointReference();
}
Vec3d Triangle3d::normal() {
	return Vec3d(l1.normal(l2));
}
void Triangle3d::put_points_in_list() {
	p1_pos = points_list->add_point(l1.p1);
	p2_pos = points_list->add_point(l2.p1);
	p3_pos = points_list->add_point(l3.p1);
}
vector<Triangle3d> Triangle3d::remove_behind_plan(Plane3d plan) {
	vector<bool> sides = { plan.in_normal_side(l1.p1), plan.in_normal_side(l2.p1), plan.in_normal_side(l3.p1) };
	if (!sides[0] && !sides[1] && !sides[2]) {
		return {};
	} else if (sides[0] && sides[1] && sides[2]) {
		return {*this};
	} else if (sides[0] && !sides[1] && !sides[2]) {
		return { Triangle3d(l1.p1, plan.intersection(l1), plan.intersection(l3), points_list) };
	} else if (!sides[0] && sides[1] && !sides[2]) {
		return { Triangle3d(l2.p1, plan.intersection(l1), plan.intersection(l2), points_list) };
	} else if (!sides[0] && !sides[1] && sides[2]) {
		return { Triangle3d(l3.p1, plan.intersection(l2), plan.intersection(l3), points_list) };
	} else if (sides[0] && sides[1] && !sides[2]) {
		Vec3d inter = plan.intersection(l3);
		return { Triangle3d(l1.p1, l2.p1, inter, points_list),
				 Triangle3d(l2.p1, plan.intersection(l2), inter, points_list) };
	} else if (!sides[0] && sides[1] && sides[2]) {
		Vec3d inter = plan.intersection(l1);
		return { Triangle3d(l2.p1, l3.p1, inter, points_list),
				 Triangle3d(l3.p1, plan.intersection(l3), inter, points_list) };
	} else {
		Vec3d inter = plan.intersection(l2);
		return { Triangle3d(l3.p1, l1.p1, inter, points_list),
				 Triangle3d(l1.p1, plan.intersection(l1), inter, points_list) };
	}
}


vector<Vec3d> Triangle3d::get_points() const {
	return { l1.p1, l2.p1, l3.p1 };
}


bool Triangle3d::operator==(Triangle3d other) {
	Vec3d points1[] = { l1.p1, l2.p1, l3.p1 };
	Vec3d points2[] = { other.l1.p1, other.l2.p1, other.l3.p1 };
	for (int i = 0; i < 3; i++) {
		bool into = false;
		for (int j = 0; j < 3; j++) {
			if (points1[i] == points2[j]) {
				points2[j] = Vec3d{ 10000, 10000, 10000 };
				into = true;
				break;
			}
		}
		if (not into) return false;
	}
	return true;
	//return l1.p1 == other.l1.p1 && l2.p1 == other.l2.p1 && l3.p1 == other.l3.p1;
}



Triangle2d Triangle3d::projected_triangle(Vec3d playerPos) {
	float d = (dist(l1.p1, playerPos) + dist(l2.p1, playerPos) + dist(l3.p1, playerPos))/3;
	return Triangle2d(points_list->access_point2d(p1_pos),
		points_list->access_point2d(p2_pos),
		points_list->access_point2d(p3_pos),
		d);
}
string Triangle3d::to_string() {
	return l1.p1.to_str() + " / " + l2.p1.to_str() + " / " + l3.p1.to_str();
}



TEST_CASE("Triangle3d remove_behind_plan") {
	Triangle3d t1 = { Vec3d{1, 0, 0}, Vec3d{-1, 0, 0}, Vec3d{-1, 2, 0}, NULL };
	SUBCASE("remove1") {
		Plane3d plan = { Vec3d{0, 0, 0}, Vec3d{1, 0, 0} };
		vector<Triangle3d> v = t1.remove_behind_plan(plan);
		CHECK(v.size() == 1);
		if (v.size() == 1)
			CHECK(v[0] == Triangle3d{ Vec3d{1, 0, 0}, Vec3d{0, 0, 0}, Vec3d{0, 1, 0}, NULL });
	}
	SUBCASE("remove2") {
		Plane3d plan = { Vec3d{0, 0, 0}, Vec3d{-1, 0, 0} };
		vector<Triangle3d> v = t1.remove_behind_plan(plan);
		CHECK(v.size() == 2);
		if (v.size() == 2) {
			CHECK(v[0] == Triangle3d{ Vec3d{-1, 0, 0}, Vec3d{-1, 2, 0}, Vec3d{0, 0, 0}, NULL });
			CHECK(v[1] == Triangle3d{ Vec3d{-1, 2, 0}, Vec3d{0, 1, 0}, Vec3d{0, 0, 0}, NULL });
		}
	}
	SUBCASE("remove3") {
		Plane3d plan = { Vec3d{2, 0, 0}, Vec3d{1, 0, 0} };
		vector<Triangle3d> v = t1.remove_behind_plan(plan);
		CHECK(v.size() == 0);
	}
}
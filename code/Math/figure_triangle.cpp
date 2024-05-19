#include "Math/figure_triangle.hpp"

#include "doctest.h"

Triangle2d::Triangle2d() {
	l1 = Line2d(); l2 = Line2d(); l3 = Line2d();
}
Triangle2d::Triangle2d(Vec2d p1, Vec2d p2, Vec2d p3) {
	l1 = Line2d(p1, p2); l2 = Line2d(p2, p3); l3 = Line2d(p3, p1);
}
vector<Vec2d> Triangle2d::get_draw_points() {
	return { l1.p1, l2.p1, l3.p1 };
}
vector<Triangle2d> Triangle2d::remove_behind_line(Line2d line) {
	vector<bool> sides = { line.in_normal_side(l1.p1), line.in_normal_side(l2.p1), line.in_normal_side(l3.p1) };
	if (!sides[0] && !sides[1] && !sides[2]) {
		return {};
	}
	else if (sides[0] && sides[1] && sides[2]) {
		return {*this};
	}
	else if (sides[0] && !sides[1] && !sides[2]) {
		return { Triangle2d(l1.p1, line.intersection(l1), line.intersection(l3)) };
	}
	else if (!sides[0] && sides[1] && !sides[2]) {
		return { Triangle2d(l2.p1, line.intersection(l1), line.intersection(l2)) };
	}
	else if (!sides[0] && !sides[1] && sides[2]) {
		return { Triangle2d(l3.p1, line.intersection(l2), line.intersection(l3)) };
	}
	else if (sides[0] && sides[1] && !sides[2]) {
		Vec2d inter = line.intersection(l3);
		return { Triangle2d(l1.p1, l2.p1, inter), Triangle2d(l2.p1, line.intersection(l2), inter) };
	}
	else if (!sides[0] && sides[1] && sides[2]) {
		Vec2d inter = line.intersection(l1);
		return { Triangle2d(l2.p1, l3.p1, inter),
				 Triangle2d(l3.p1, line.intersection(l3), inter) };
	}
	else {
		Vec2d inter = line.intersection(l2);
		return { Triangle2d(l3.p1, l1.p1, inter),
				 Triangle2d(l1.p1, line.intersection(l1), inter) };
	}
}
bool Triangle2d::operator==(Triangle2d o) {
	return l1.p1 == o.l1.p1 && l2.p1 == o.l2.p1 && l3.p1 == o.l3.p1;
}
string Triangle2d::to_str() {
	return l1.p1.to_str() + "  --  " + l2.p1.to_str() + "  --  " + l3.p1.to_str();
}



TEST_CASE("triangle2d") {
	Triangle2d t1 = Triangle2d(vec(0, 0), vec(1, 1), vec(1, 0));
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
			CHECK(t[0] == Triangle2d(vec(0, 0), vec(0.5, 0.5), vec(0.5, 0)));
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
bool Triangle3d::operator==(Triangle3d other) {
	return l1.p1 == other.l1.p1 && l2.p1 == other.l2.p1 && l3.p1 == other.l3.p1;
}
Triangle2d Triangle3d::projected_triangle() {
	return Triangle2d(points_list->access_point2d(p1_pos),
		points_list->access_point2d(p2_pos),
		points_list->access_point2d(p3_pos));
}
string Triangle3d::to_string() {
	return l1.p1.to_str() + " / " + l2.p1.to_str() + " / " + l3.p1.to_str();
}
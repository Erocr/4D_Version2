#ifndef TRIANGLE
#define TRIANGLE


#include "Math/vectors.hpp"
#include "Math/line.hpp"
#include "Engine3d/points_list.hpp"
#include "Math/plane.hpp"

class Triangle2d {
public:
	Triangle2d();
	Triangle2d(Vec2d p1, Vec2d p2, Vec2d p3, float d);
	vector<Vec2d> get_draw_points();
	vector<Triangle2d> remove_behind_line(Line2d line);

	float getDist();
	
	string to_str();

	bool operator==(Triangle2d other);
private:
	Line2d l1, l2, l3;
	float d;
};


class Triangle3d {
private:
	PointsList* points_list; PointReference p1_pos; PointReference p2_pos; PointReference p3_pos;
public:
	Line3d l1; Line3d l2; Line3d l3;
	Triangle3d();
	Triangle3d(Vec3d p1, Vec3d p2, Vec3d p3, PointsList* pointsList);
	Vec3d normal();
	void put_points_in_list();
	vector<Triangle3d> remove_behind_plan(Plane3d plan);
	vector<Vec3d> get_points() const;
	bool operator==(Triangle3d other);
	string to_string();
	Triangle2d projected_triangle(Vec3d playerPos);
};



#endif
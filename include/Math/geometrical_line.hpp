#ifndef LINE
#define LINE

#include "Math/geometrical_vectors.hpp"


class Line2d {
public:
	Vec2d normal;
	Vec2d p1; Vec2d p2;
	Line2d();
	Line2d(Vec2d p1, Vec2d p2);
	Line2d(Vec2d p1, Vec2d p2, Vec2d normal);
	bool in_normal_side(Vec2d p);
	// @return Vec2d(0, 0) if there is no intersections
	Vec2d intersection(Line2d other);
};

class Line3d {
public:
	Vec3d p1; Vec3d p2; Vec3d dir;
	Line3d();
	Line3d(Vec3d point1, Vec3d point2);
	Vec3d normal(Line3d other);
};


class Line4d {
public:
	Vec4d p1; Vec4d p2; Vec4d dir;
	Line4d();
	Line4d(Vec4d point1, Vec4d point2);
};

#endif
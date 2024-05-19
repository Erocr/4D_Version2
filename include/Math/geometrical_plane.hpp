#ifndef PLANE
#define PLANE

#include "Math/geometrical_vectors.hpp"
#include "Math/geometrical_line.hpp"

class Plane3d {
public:
	Vec3d point; Vec3d normal;
	Plane3d(Vec3d p, Vec3d n);
	void rotate(float radians, int axis);
	void move(Vec3d added_vector);
	bool in_normal_side(Vec3d p);
	Vec3d intersection(Line3d line);
};

#endif
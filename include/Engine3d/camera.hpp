#ifndef CAMERA
#define CAMERA

#include "Math/vectors.hpp"
#include "Math/plane.hpp"
#include <vector>

class Camera {
public:
	float angle_x; float angle_y; float angle_z; float aspect_ratio; double factor;
	Vec3d pos; float z_far; float z_near; float z_q;  double fov; Vec3d dir;
	Camera(Vec3d position, float angle_x, float angle_y, float angle_z);
	void update_dir();
	void move(Vec3d added_vector);
	void rotate(float radians, int axis);
	void set_aspect_ratio(float new_aspect_ratio);
	Plane3d get_front_plan();
};

Vec2d projection(Vec3d point, Camera cam);

#endif
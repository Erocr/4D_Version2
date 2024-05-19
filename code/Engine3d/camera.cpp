#include "Engine3d/camera.hpp"

Camera::Camera(Vec3d position, float angle_x, float angle_y, float angle_z) {
	pos = position; this->angle_x = angle_x; this->angle_y = angle_y; this->angle_z = angle_z;
	update_dir();
	z_far = 100; z_near = 0.1; 
	z_q = z_far / (z_far - z_near);
	fov = PI / 2;
	factor = 1 / tan(fov / 2);
	aspect_ratio = 1;
}
void Camera::update_dir() {
	dir = Vec3d(0, 0, 1);
	dir.rotate(angle_x, 0);
	dir.rotate(angle_y, 1);
}
void Camera::move(Vec3d added_vector) {
	pos = pos.add(added_vector);
}
void Camera::rotate(float radians, int axis) {
	if (axis == 0) {
		angle_x += radians;
		dir = dir.rotate(-radians, 0);
	}
	else if (axis == 1) {
		angle_y += radians;
		dir = dir.rotate(-radians, 1);
	}
	else { 
		angle_z += radians; 
		dir = dir.rotate(-radians, 2);
	}
}
void Camera::set_aspect_ratio(float new_aspect_ratio) {
	aspect_ratio = new_aspect_ratio;
}
Plane3d Camera::get_front_plan() {
	Plane3d res(pos, dir);
	res.move(dir.mul(z_near));
	return res;
}

Vec2d projection(Vec3d vec, Camera cam) {
	vec = vec.sub(cam.pos);
	Vec3d new_vec = vec.rotate(cam.angle_y, 1).rotate(cam.angle_z, 2).rotate(cam.angle_x, 0);
	float divided = (new_vec.z * cam.z_q - cam.z_near * cam.z_q);
	return Vec2d(cam.aspect_ratio * cam.factor * new_vec.x / divided,
		cam.factor * new_vec.y / divided);
}
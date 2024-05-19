#include "Engine3d/points_list.hpp"

PointReference::PointReference() {
	hash = -1; collision_position = -1;
}

int position(vector<Vec3d> list, Vec3d point) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == point) {
			return i;
		}
	}
	return -1;
}

PointsList::PointsList() {
	points3d = vector<vector<Vec3d>>(100, vector<Vec3d>(0));
	points2d = vector<vector<Vec2d>>(100, vector<Vec2d>(0));
}
PointReference PointsList::add_point(Vec3d point) {
	PointReference p_ref = PointReference();
	p_ref.hash = point.hash();
	int pos = position(points3d[p_ref.hash], point);
	if (pos == -1) {
		p_ref.collision_position = points3d[p_ref.hash].size();
		points3d[p_ref.hash].push_back(point);
	} else {
		p_ref.collision_position = pos;
	}
	return p_ref;
}
void PointsList::reset_points() {
	for (int i = 0; i < 100; i++) {
		points3d = vector<vector<Vec3d>>(100, vector<Vec3d>(0));
		points2d = vector<vector<Vec2d>>(100, vector<Vec2d>(0));
	}
}
void PointsList::project_points(Camera cam) {
	points2d = vector<vector<Vec2d>>(points3d.size());
	for (int i = 0; i < points3d.size(); i++) {
		points2d[i] = vector<Vec2d>(points3d[i].size());
	}
	for (int i = 0; i < points3d.size(); i++) {
		for (int j = 0; j < points3d[i].size(); j++) {
			points2d[i][j] = projection(points3d[i][j], cam);
		}
	}
}
Vec2d PointsList::access_point2d(PointReference p_ref) {
	return points2d[p_ref.hash][p_ref.collision_position];
}

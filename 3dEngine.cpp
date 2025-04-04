#include <Engine3d/3dEngine.hpp>
using namespace std;


#include "doctest.h"

Camera Engine3d::init_cam(View view) {
	Camera res(Vec3d(0, 0, 0), 0, 0, 0);
	res.set_aspect_ratio(view.get_aspect_ratio());
	return res;
}



Engine3d::Engine3d(View &view) : points_list{}, cam{init_cam(view)} {
	models3d = {};
}


Engine3d::Engine3d(View& view, bool debug) : points_list{}, cam{ init_cam(view) } {
	models3d = { cube(Vec3d(-1, -1, 3), Vec3d(1, 1, 5), &points_list) };
}

PointsList* Engine3d::getPointsList() {
	return &points_list;
}


vector<Triangle2d> Engine3d::getProjectedTriangles() {
	vector<Triangle2d> res(0);
	for (Model3d& model : models3d) {
		vector<Triangle2d> to_add = model.getProjected();
		res.insert(res.begin(), to_add.begin(), to_add.end());
	}
	return res;
}


vector<vector<Vec2d>> Engine3d::triangles_to_draw() {
	points_list.reset_points();
	for (int i = 0; i < models3d.size(); i++) {
		models3d[i].remove_behind(cam);
		models3d[i].put_points_in_list();
	}
	points_list.project_points(cam);
	for (Model3d& model : models3d) {
		model.set_triangles_projected(cam.pos);
		model.remove_not_visible2d();
	}
	vector<Triangle2d> triangles = getProjectedTriangles();

	sort(triangles.begin(), triangles.end(), [](Triangle2d a, Triangle2d b) { return a.getDist() > b.getDist(); });

	vector<vector<Vec2d>> res(0);
	for (Triangle2d & triangle: triangles) {
		res.push_back(triangle.get_draw_points());
	}
	return res;
}


void Engine3d::rotateCam(float radians, int axis) {
	cam.rotate(radians, axis);
}

void Engine3d::moveCam(Vec3d addedVector) {
	cam.move(addedVector);
}

Vec3d Engine3d::getDir() const {
	return cam.dir;
}

void Engine3d::setModels(vector<Model3d> & new_models) {
	models3d = new_models;
}
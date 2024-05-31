#include "Engine3d/model3d.hpp"
#include <iostream>

Model3d::Model3d(vector<Triangle3d> triangles) {
	this->triangles = triangles;
	triangles_cutted = triangles;
	triangles_projected = {};
}

bool Model3d::empty() {
	return triangles.size() == 0;
}

void Model3d::put_points_in_list() {
	for (int i = 0; i < triangles_cutted.size(); i++) {
		triangles_cutted[i].put_points_in_list();
	}
}
void Model3d::remove_behind(Camera cam) {
	set_triangles_cutted();
	Plane3d plan = cam.get_front_plan();
	vector<Triangle3d> new_triangles_cutted = vector<Triangle3d>(2 * triangles.size());
	int tri_cut_index = 0;
	vector<Triangle3d> tri_temp;
	for (int i = 0; i < triangles.size(); i++) {
		tri_temp = triangles[i].remove_behind_plan(plan);
		for (int j = 0; j < tri_temp.size(); j++) {
			new_triangles_cutted[tri_cut_index] = tri_temp[j];
			tri_cut_index++;
		}
	}
	triangles_cutted = new_triangles_cutted;
	triangles_cutted.resize(tri_cut_index);
}
void Model3d::set_triangles_projected(Vec3d playerPos) {
	triangles_projected = vector<Triangle2d>(triangles_cutted.size());
	for (int i = 0; i < triangles_cutted.size(); i++) {
		triangles_projected[i] = triangles_cutted[i].projected_triangle(playerPos);
	}
}
void Model3d::set_triangles_cutted() {
	triangles_cutted = triangles;
}
void Model3d::remove_behind_edge(Line2d edge) {
	vector<Triangle2d> new_triangles_projected = vector<Triangle2d>(2 * triangles_projected.size());
	int tri_proj_index = 0;
	vector<Triangle2d> tri_temp;
	for (int i = 0; i < triangles_projected.size(); i++) {
		tri_temp = triangles_projected[i].remove_behind_line(edge);
		for (int j = 0; j < tri_temp.size(); j++) {
			new_triangles_projected[tri_proj_index] = tri_temp[j];
			tri_proj_index++;
		}
	}
	triangles_projected = new_triangles_projected;
	triangles_projected.resize(tri_proj_index);
}
void Model3d::remove_not_visible2d() {
	vector<Line2d> screen_edges(4);
	screen_edges[0] = Line2d(Vec2d(-1, -1), Vec2d(1, -1), Vec2d(0, 1));
	screen_edges[1] = Line2d(Vec2d(1, -1), Vec2d(1, 1), Vec2d(-1, 0));
	screen_edges[2] = Line2d(Vec2d(1, 1), Vec2d(-1, 1), Vec2d(0, -1));
	screen_edges[3] = Line2d(Vec2d(-1, 1), Vec2d(-1, -1), Vec2d(1, 0));
	for (const Line2d &edge : screen_edges) {
		remove_behind_edge(edge);
	}
}

vector<Triangle2d> Model3d::getProjected() {
	return triangles_projected;
}

vector<vector<Vec2d>> Model3d::get_draw_points() {
	vector<vector<Vec2d>> res(triangles_projected.size());
	for (int i = 0; i < triangles_projected.size(); i++) {
		res[i] = triangles_projected[i].get_draw_points();
	}
	return res;
}




Model3d cube(Vec3d p1, Vec3d p2, PointsList* pl) {
	vector<Vec3d> points = { p1, p1, p1, p1, p2, p2, p2, p2 };
	points[1].x = p2.x;
	points[2].y = p2.y;
	points[3].x = p2.x; points[3].y = p2.y;
	points[4].x = p1.x; points[4].y = p1.y;
	points[5].y = p1.y;
	points[6].x = p1.x;
	return Model3d({ Triangle3d(points[0], points[1], points[2], pl) ,
					 Triangle3d(points[1], points[2], points[3], pl),
					 Triangle3d(points[1], points[5], points[7], pl),
					 Triangle3d(points[1], points[7], points[3], pl),
					 Triangle3d(points[5], points[4], points[6], pl),
					 Triangle3d(points[5], points[6], points[7], pl),
					 Triangle3d(points[4], points[5], points[1], pl),
					 Triangle3d(points[4], points[1], points[0], pl),
					 Triangle3d(points[2], points[3], points[7], pl),
					 Triangle3d(points[2], points[7], points[6], pl),
					 Triangle3d(points[4], points[0], points[2], pl),
					 Triangle3d(points[4], points[2], points[6], pl), });
}
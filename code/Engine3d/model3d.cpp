#include "Engine3d/model3d.hpp"
#include <iostream>

Model3d::Model3d(vector<Triangle3d> triangles) {
	this->triangles = triangles;
	triangles_cutted = triangles;
	triangles_projected = {};
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
void Model3d::set_triangles_projected() {
	triangles_projected = vector<Triangle2d>(triangles_cutted.size());
	for (int i = 0; i < triangles_cutted.size(); i++) {
		triangles_projected[i] = triangles_cutted[i].projected_triangle();
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
vector<vector<Vec2d>> Model3d::get_draw_points() {
	vector<vector<Vec2d>> res(triangles_projected.size());
	for (int i = 0; i < triangles_projected.size(); i++) {
		res[i] = triangles_projected[i].get_draw_points();
	}
	return res;
}
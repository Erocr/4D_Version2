#pragma once

#include "View/draw_SDL.hpp"

#include <Math/geometrical_line.hpp>
#include <Math/geometrical_vectors.hpp>
#include "Math/geometrical_line.hpp"
#include "Math/geometrical_plane.hpp"
#include "Math/geometrical_space.hpp"
#include "Math/figure_triangle.hpp"
#include "Engine3d/camera.hpp"
#include "Engine3d/model3d.hpp"
#include "Math/sort.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <utility>
#include <cstdlib>


class Engine3d {
public:
	Engine3d(View &view);
	Engine3d(View& view, bool debug);

	vector<vector<Vec2d>> triangles_to_draw();
	void rotateCam(float radians, int axis);
	void moveCam(Vec3d addedVector);
	Vec3d getDir() const;

	void setModels(vector<Model3d> &new_models);
	PointsList* getPointsList();
private:
	Camera init_cam(View view);

	PointsList points_list;
	Camera cam;
	vector<Model3d> models3d;
};
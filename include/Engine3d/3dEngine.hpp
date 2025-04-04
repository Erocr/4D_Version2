#pragma once

#include "View/draw_SDL.hpp"

#include <Math/line.hpp>
#include <Math/vectors.hpp>
#include "Math/plane.hpp"
#include "Math/space.hpp"
#include "Math/triangle.hpp"
#include "Engine3d/camera.hpp"
#include "Engine3d/model3d.hpp"
#include "Math/sort.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <utility>
#include <cstdlib>
#include <algorithm>


class Engine3d {
public:
	Engine3d(View &view);
	Engine3d(View &view, bool debug);

	vector<vector<Vec2d>> triangles_to_draw();
	void rotateCam(float radians, int axis);
	void moveCam(Vec3d addedVector);
	Vec3d getDir() const;

	void setModels(vector<Model3d> &new_models);
	PointsList* getPointsList();
private:
	Camera init_cam(View view);
	vector<Triangle2d> getProjectedTriangles();

	PointsList points_list;
	Camera cam;
	vector<Model3d> models3d;
};
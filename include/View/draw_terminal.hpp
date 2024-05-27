#pragma once

#include "Math/geometrical_vectors.hpp"
#include <vector>
using namespace std;

class View {
public:
	View() : _ZCamRotation{ 0 }, _YCamRotation{ 0 }, _forwardMove{ 0 }, _rightMove{ 0 }, 
		_upMove{ 0 }, _exit{ false } {}

	void draw_2d_triangles(vector<vector<Vec2d>> triangles);
	float get_aspect_ratio();

	void inputsUpdate();

	float ZCamRotation() const { return _ZCamRotation; }
	float YCamRotation() const { return _YCamRotation; }
	float forwardMove() const { return _forwardMove; }
	float rightMove() const { return _rightMove; }
	float upMove() const { return _upMove; }
	bool exit() const { return _exit; }

private:

	bool in_triangles(vector<vector<Vec2d>> triangles, Vec2d pos);
	bool in_triangle(vector<Vec2d> triangle, Vec2d pos);

	float _ZCamRotation;
	float _YCamRotation;
	float _forwardMove;
	float _rightMove;
	float _upMove;
	bool _exit;
};

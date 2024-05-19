#pragma once

#include "Math/geometrical_vectors.hpp"
#include <vector>
using namespace std;

class View {
public:
	View() : _XCamRotation{ 0 }, _YCamRotation{ 0 }, _forwardMove{ 0 }, _rightMove{ 0 }, 
		_upMove{ 0 }, _exit{ false } {}

	void draw_2d_triangles(vector<vector<Vec2d>> triangles);
	float get_aspect_ratio();

	void inputsUpdate();

	float XCamRotation() const { return _XCamRotation; }
	float YCamRotation() const { return _YCamRotation; }
	int forwardMove() const { return _forwardMove; }
	int rightMove() const { return _rightMove; }
	int upMove() const { return _upMove; }
	bool exit() const { return _exit; }

private:

	bool in_triangles(vector<vector<Vec2d>> triangles, Vec2d pos);
	bool in_triangle(vector<Vec2d> triangle, Vec2d pos);

	float _XCamRotation;
	float _YCamRotation;
	int _forwardMove;
	int _rightMove;
	int _upMove;
	bool _exit;
};

#pragma once

#include <Math/geometrical_vectors.hpp>
#include <vector>
#include <SDL2/SDL.h>
using namespace std;

class View {
public:
	View();

	void draw_2d_triangles(vector<vector<Vec2d>> triangles);
	float get_aspect_ratio();

	void inputsUpdate();

	float XCamRotation() const { return _XCamRotation; }
	float YCamRotation() const { return _YCamRotation; }
	float forwardMove() const { return _forwardMove; }
	float rightMove() const { return _rightMove; }
	float upMove() const { return _upMove; }
	bool exit() const { return _exit; }

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width;
	int height;

	void clear();

	float _XCamRotation;
	float _YCamRotation;
	float _forwardMove;
	float _rightMove;
	float _upMove;
	bool _exit;
};
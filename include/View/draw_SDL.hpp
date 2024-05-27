#pragma once

#include <Math/geometrical_vectors.hpp>
#include <vector>
#include <SDL2/SDL.h>
#include <Math/figure_triangle.hpp>
using namespace std;

struct Color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;

	Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a): r{_r}, g{_g}, b{_b}, a{_a}  {}
	Color(Uint8 _r, Uint8 _g, Uint8 _b): r{ _r }, g{ _g }, b{ _b }, a{ 255 }   {}
	Color(): r{ 0 },  g{ 0 }, b{ 0 }, a{ 255 }                                 {}
};

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

	void drawLine(Vec2d p1, Vec2d p2);
	void drawTriangle(Vec2d p1, Vec2d p2, Vec2d p3);
	Vec2d toCoord(Vec2d v);
};
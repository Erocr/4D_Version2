#pragma once

#include "Math/geometrical_vectors.hpp"
#include <vector>
using namespace std;

float get_aspect_ratio();

void draw_2d_triangles(vector<vector<Vec2d>> triangles);

bool in_triangles(vector<vector<Vec2d>> triangles, Vec2d pos);

bool in_triangle(vector<Vec2d> triangle, Vec2d pos);

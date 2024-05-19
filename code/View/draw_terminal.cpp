#include "View/draw_terminal.hpp"
#include <iostream>;
#include <stdlib.h>
#include <stdexcept>
using namespace std;



float View::get_aspect_ratio() {
	return 0.7;
}

void set_line(Vec2d p1, Vec2d p2, vector<vector<bool>>* to_draw) {
	if (p1.x > 1 || p2.x > 1) throw runtime_error("A point is not well cutted (right side)");
	if (p1.x < -1 || p2.x < -1) throw runtime_error("A point is not well cutted (left side)");
	if (p1.y > 1 || p2.y > 1) throw runtime_error("A point is not well cutted (down side)");
	if (p1.y < -1 || p2.y < -1) throw runtime_error("A point is not well cutted (up side)");
	p1.x = (p1.x + 1) / 2 * 120;
	p1.y = (p1.y + 1) / 2 * 25;
	p2.x = (p2.x + 1) / 2 * 120;
	p2.y = (p2.y + 1) / 2 * 25;
	Vec2d add = p2.sub(p1).normalise();
	Vec2d p = p1;
	while (p.sub(p2).size() > 1) {
		(*to_draw)[int(p.y)][int(p.x)] = true;
		p = p.add(add);
	}
}

void View::draw_2d_triangles(vector<vector<Vec2d>> triangles) {
	//system("CLS");
	vector<vector<bool>> to_draw = vector<vector<bool>>(26, vector<bool>(121));
	for (int i=0; i<triangles.size(); i++) {
		set_line(triangles[i][0], triangles[i][1], &to_draw);
		set_line(triangles[i][1], triangles[i][2], &to_draw);
		set_line(triangles[i][2], triangles[i][0], &to_draw);
	}
	for (float y = 0; y < 25; y ++) {
		for (float x = 0; x < 120; x ++) {
			if (to_draw[y][x]) {
				cout << "0";
			}
			else {
				cout << " ";
			}
		}
		cout << "\n";
	}
}


bool View::in_triangles(vector<vector<Vec2d>> triangles, Vec2d pos) {
	for (vector<Vec2d> triangle : triangles) {
		if (in_triangle(triangle, pos)) {
			return true;
		}
	}
	return false;
}


bool View::in_triangle(vector<Vec2d> triangle, Vec2d pos) {
	Vec2d v1(triangle[1].x - triangle[0].x, triangle[1].y - triangle[0].y);
	Vec2d v2(triangle[2].x - triangle[1].x, triangle[2].y - triangle[1].y);
	Vec2d v3(triangle[0].x - triangle[2].x, triangle[0].y - triangle[2].y);
	bool first_direction = triangle[0].is_right_side(v1, pos);
	if (first_direction != triangle[1].is_right_side(v2, pos) or first_direction != triangle[2].is_right_side(v3, pos)) return false;
	return true;
}


void View::inputsUpdate() {
	_XCamRotation = 0;
	_YCamRotation = 0;
	_forwardMove = 0;
	_rightMove = 0;
	_upMove = 0;
	_exit = false;

	string player_decision;
	cin >> player_decision;
	for (int i = 0; i < player_decision.size(); i++) {
		switch (player_decision[i]) {
		case 'z': _forwardMove++; break;
		case 'd': _rightMove++; break;
		case 'q': _rightMove--; break;
		case 's': _forwardMove--; break;
		case 'i': _upMove++; break;
		case 'k': _upMove--; break;
		case 'e': _XCamRotation += PI/4; break;
		case 'a': _XCamRotation -= PI/4; break;
		}
	}
}
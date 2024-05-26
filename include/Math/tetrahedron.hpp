#pragma once

#include <Math/geometrical_vectors.hpp>
#include <Math/geometrical_space.hpp>
#include <Math/figure_triangle.hpp>
#include <Math/geometrical_line.hpp>
#include <vector>
#include <array>

class Tetrahedron {
public:
	Tetrahedron(Vec4d _p1, Vec4d _p2, Vec4d _p3, Vec4d _p4) : p1{ _p1 }, p2{ _p2 }, p3{ _p3 }, p4{ _p4 }
	{
		lines[0] = Line4d(p1, p2);
		lines[1] = Line4d(p2, p3);
		lines[2] = Line4d(p3, p1);
		lines[3] = Line4d(p1, p4);
		lines[4] = Line4d(p2, p4);
		lines[5] = Line4d(p3, p4);
	}
	vector<Vec4d> intersection(Space& space);

private:
	int bool2sides(bool b1, bool b2, bool b3, bool b4);
	vector<Line4d> useful_lines(int sides);
	Vec4d p1;
	Vec4d p2;
	Vec4d p3;
	Vec4d p4;
	Line4d lines[6];
};
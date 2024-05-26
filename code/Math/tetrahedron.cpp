#include <Math/tetrahedron.hpp>


int Tetrahedron::bool2sides(bool b1, bool b2, bool b3, bool b4) {
	return b1 * 8 + b2 * 4 + b3 * 2 + b4;
}

vector<Line4d> Tetrahedron::useful_lines(int sides) {
	if (sides > 7) sides = 14 - sides;
	if (sides == 0) return {};
	else if (sides == 1) return { lines[3], lines[4], lines[5] };
	else if (sides == 2) return { lines[1], lines[2], lines[5] };
	else if (sides == 3) return { lines[1], lines[2], lines[3], lines[4] };
	else if (sides == 4) return { lines[0], lines[1], lines[4] };
	else if (sides == 5) return { lines[0], lines[1], lines[5], lines[3] };
	else if (sides == 6) return { lines[0], lines[2], lines[5], lines[4] };
	else if (sides == 7) return { lines[0], lines[2], lines[3] };
	else throw runtime_error("sides doit respecter: 0 <= sides <= 14");
}

vector<Triangle3d> Tetrahedron::intersection(Space& space, PointsList *pl) {
	vector<Line4d> cool_lines = useful_lines(bool2sides(
		space.in_normal_side(p1),
		space.in_normal_side(p2),
		space.in_normal_side(p3),
		space.in_normal_side(p4)
	));
	vector<Vec3d> res = {};
	for (Line4d& line : cool_lines) {
		res.push_back(space.changingBase(space.intersection(line)));
	}
	if (res.size() == 0) return {};
	else if (res.size() == 3) return { Triangle3d(res[0], res[1], res[2], pl) };
	else return { Triangle3d(res[0], res[1], res[2], pl), Triangle3d(res[0], res[2], res[3], pl) };
}
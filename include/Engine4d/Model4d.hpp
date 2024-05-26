#pragma once

#include <Math/geometrical_vectors.hpp>
#include <Math/tetrahedron.hpp>
#include <Math/geometrical_space.hpp>
#include <vector>
#include <Engine3d/model3d.hpp>


class Model4d {
public:
	Model4d(vector<Tetrahedron> t);
	Model4d(Tetrahedron* t, int size);
	
	Model3d cut(Space space, PointsList *p);

private:
	vector<Tetrahedron> tetrahedrons;
};


Model4d hypercube(Vec4d p1, Vec4d p2);
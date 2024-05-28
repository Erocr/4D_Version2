#include <Engine4d/Model4d.hpp>


Model4d::Model4d(vector<Tetrahedron> t) : tetrahedrons{t}  {}


Model4d::Model4d(Tetrahedron* t, int size) {
	tetrahedrons = {};
	for (int i = 0; i < size; i++) {
		tetrahedrons.push_back(t[i]);
	}
}


Model3d Model4d::cut(Space space, PointsList* pl) {
	vector<Triangle3d> triangles = {};
	for (Tetrahedron& tetrahedron : tetrahedrons) {
		vector<Triangle3d> news = tetrahedron.intersection(space, pl);
		triangles.insert(triangles.end(), news.begin(), news.end());
	}
	return Model3d{ triangles };
}


/* @return un tableau de 5 tétrahèdres
*/
Tetrahedron* cubeTetrahedrons(Vec4d p1, Vec4d p2, Vec4d p3, Vec4d p4, Vec4d p5, Vec4d p6, Vec4d p7, Vec4d p8, Tetrahedron *first) {
	first[0] = Tetrahedron(p3, p1, p7, p4);
	first[1] = Tetrahedron(p1, p2, p4, p6);
	first[2] = Tetrahedron(p8, p7, p6, p4);
	first[3] = Tetrahedron(p1, p7, p4, p6);
	first[4] = Tetrahedron(p7, p5, p1, p6);
	return first+5;
}


Model4d hypercube(Vec4d p1, Vec4d p2) {
	Tetrahedron tetrahedrons[8 * 5];
	Vec4d pts[16] = { p1,
		{p2.x, p1.y, p1.z, p1.w},
		{p1.x, p2.y, p1.z, p1.w},
		{p2.x, p2.y, p1.z, p1.w},
		{p1.x, p1.y, p2.z, p1.w},
		{p2.x, p1.y, p2.z, p1.w},
		{p1.x, p2.y, p2.z, p1.w},
		{p2.x, p2.y, p2.z, p1.w},
		{p1.x, p1.y, p1.z, p2.w},
		{p2.x, p1.y, p1.z, p2.w},
		{p1.x, p2.y, p1.z, p2.w},
		{p2.x, p2.y, p1.z, p2.w},
		{p1.x, p1.y, p2.z, p2.w},
		{p2.x, p1.y, p2.z, p2.w},
		{p1.x, p2.y, p2.z, p2.w},
		p2 };
	Tetrahedron* first = tetrahedrons;
	first = cubeTetrahedrons(pts[4], pts[5], pts[6], pts[7], pts[0], pts[1], pts[2], pts[3], first);
	first = cubeTetrahedrons(pts[8], pts[9], pts[10], pts[11], pts[12], pts[13], pts[14], pts[15], first);
	first = cubeTetrahedrons(pts[1], pts[9], pts[3], pts[11], pts[5], pts[13], pts[7], pts[15], first);
	first = cubeTetrahedrons(pts[8], pts[0], pts[10], pts[2], pts[12], pts[4], pts[14], pts[6], first);
	first = cubeTetrahedrons(pts[2], pts[3], pts[10], pts[11], pts[6], pts[7], pts[14], pts[15], first);
	first = cubeTetrahedrons(pts[8], pts[9], pts[0], pts[1], pts[12], pts[13], pts[4], pts[5], first);
	first = cubeTetrahedrons(pts[4], pts[5], pts[6], pts[7], pts[12], pts[13], pts[14], pts[15], first);
	first = cubeTetrahedrons(pts[8], pts[9], pts[10], pts[11], pts[0], pts[1], pts[2], pts[3], first);
	return Model4d(tetrahedrons, 8 * 5);
}
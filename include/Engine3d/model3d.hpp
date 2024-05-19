#ifndef MODEL3D
#define MODEL3D

#include "Math/geometrical_vectors.hpp"
#include "Math/figure_triangle.hpp"
#include "Math/geometrical_plane.hpp"
#include "Engine3d/camera.hpp"
#include <vector>
using namespace std;


class Model3d {
public:
	vector<Triangle3d> triangles;
	vector<Triangle3d> triangles_cutted;
	vector<Triangle2d> triangles_projected;
	Model3d(vector<Triangle3d> triangles);
	void remove_behind(Camera cam);
	void put_points_in_list();
	vector<vector<Vec2d>> get_draw_points();
	void set_triangles_projected();
	void remove_not_visible2d();
private:
	void set_triangles_cutted();
	void remove_behind_edge(Line2d edge);
};


#endif
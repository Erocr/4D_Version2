#ifndef POINTSLIST
#define POINTSLIST

#include <vector>
#include "Math/vectors.hpp"
#include "Engine3d/camera.hpp"
using namespace std;

struct PointReference {
	int hash; int collision_position;
	PointReference();
};

class PointsList {
public:
	PointsList();
	PointReference add_point(Vec3d point);
	void reset_points();
	void project_points(Camera);
	Vec2d access_point2d(PointReference p_ref);

private:
	vector<vector<Vec3d>> points3d; 
	vector<vector<Vec2d>> points2d;
};

#endif
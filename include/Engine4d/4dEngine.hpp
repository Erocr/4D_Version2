#include <Engine4d/model4d.hpp>
#include <Engine3d/3dEngine.hpp>


class Engine4d {
public:
	Engine4d(vector<Model4d> _models, View &view);

	vector<vector<Vec2d>> triangles_to_draw();

	// axis est successivement pour les axes xy, xz, xw, yz, yw, zw
	void rotate(float angle, int axis);
	void move(Vec4d addedPos);
	Vec4d getDir() const;
private:
	vector<Model4d> models;
	Engine3d engine3d;
	Space space;
};
#include <Engine4d/model4d.hpp>
#include <Engine3d/3dEngine.hpp>


class Engine4d {
public:
	Engine4d(vector<Model4d> _models, View &view);

	vector<vector<Vec2d>> triangles_to_draw();
private:
	vector<Model4d> models;
	Engine3d engine3d;
	Space space;
};
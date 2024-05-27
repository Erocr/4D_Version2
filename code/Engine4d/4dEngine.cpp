#include <Engine4d/4dEngine.hpp>

Engine4d::Engine4d(vector<Model4d> _models, View& view) : models{ _models }, engine3d{ view }, space{}  {}



vector<vector<Vec2d>> Engine4d::triangles_to_draw() {
	vector<Model3d> models3d = {};
	for (int i = 0; i < models.size(); i++) {
		Model3d to_add = models[i].cut(space, engine3d.getPointsList());
		if (not to_add.empty())
			models3d.push_back(to_add);
	}
	engine3d.setModels(models3d);
	return engine3d.triangles_to_draw();
}

using namespace std;  // Pour les exceptions dans la version distribuée

#include "View/draw_SDL.hpp"

#include <Math/geometrical_line.hpp>
#include <Math/geometrical_vectors.hpp>
#include "Math/geometrical_line.hpp"
#include "Math/geometrical_plane.hpp"
#include "Math/geometrical_space.hpp"
#include "Math/figure_triangle.hpp"
#include "Engine3d/camera.hpp"
#include "Engine3d/model3d.hpp"
#include "Math/sort.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <utility>
#include <cstdlib>
using namespace std;


#include "doctest.h"

//TEST_CASE("planes") {};

/*
	cout << "testing spaces ... ";
	cout << "test complete \n";

	cout << "testing points_list ... ";
	PointsList pl = PointsList();
	pl.add_point(Vec3d(0, 0, 0));
	pl.add_point(Vec3d(0, 2, 1));
	CHECK(pl.points3d[0][0] == Vec3d(0, 0, 0));
	CHECK(pl.points3d[3][0] == Vec3d(0, 2, 1));
	pl.reset_points();
	CHECK(pl.points3d[0].size() == 0);
	cout << "test complete \n";

	cout << "testing triangles ... ";
	Triangle3d tri = Triangle3d(Vec3d(-1, 0, 0), Vec3d(1, 2, 0), Vec3d(1, 0, 0), &pl);
	Triangle3d test = Triangle3d(Vec3d(-1, 0, 0), Vec3d(0, 1, 0), Vec3d(0, 0, 0), &pl);
	CHECK(tri.remove_behind_plan(Plane3d(Vec3d(0, 0, 0), Vec3d(-1, 0, 0)))[0] == test, "splitting 3d");
	Triangle2d tri2 = Triangle2d(Vec2d(-1, 0), Vec2d(1, 2), Vec2d(1, 0));
	Triangle2d test2 = Triangle2d(Vec2d(-1, 0), Vec2d(0, 1), Vec2d(0, 0));
	cout << tri2.remove_behind_line(Line2d(Vec2d(0, 0), Vec2d(0, 1), Vec2d(-1, 0)))[0].to_str();
	CHECK(tri2.remove_behind_line(Line2d(Vec2d(0, 0), Vec2d(0, 1), Vec2d(-1, 0)))[0] == test2, "splitting 2d");
	cout << "test complete \n";

	cout << "testing sorting algorithms ... ";
	vector<pair<int, int>> to_sort = { {156, 156}, {85, 85}, {272, 272}, {91, 91}, {14, 14}, {349, 349} };
	CHECK(radixsort<int>(to_sort, 2) == vector<int>({14, 85, 91, 156, 272, 349}), "radixsort");
	CHECK(quicksort<int>(to_sort) == vector<int>({ 14, 85, 91, 156, 272, 349 }), "quicksort");
	if (testing_times) {
		for (int j = 0; j < 10; j++) {
			vector<pair<int, int>> to_sort_big(pow(10, j));
			int to_add;
			for (int i = 0; i < pow(10, j); i++) {
				to_add = rand() % 100;
				to_sort_big[i] = pair<int, int>(to_add, to_add);
			}
			time_t start = time(NULL);
			vector<int> sorted_big = radixsort<int>(to_sort_big, 2);
			cout << "Sorting of " << pow(10, j) << " elements completed in " << difftime(time(NULL), start) << " seconds ! \n";
		}
	}
	cout << "test complete \n";

	cout << "testing terminal ... ";
	vector<Vec2d> triangle(3);
	triangle[0] = Vec2d(0, 0);
	triangle[1] = Vec2d(0, 10);
	triangle[2] = Vec2d(10, 0);
	CHECK(in_triangle(triangle, Vec2d(2, 2)), "triangle 1");
	CHECK(!in_triangle(triangle, Vec2d(10, 10)), "triangle 2");
	CHECK(in_triangle(triangle, Vec2d(0, 6)), "triangle 3");
	vector<Vec2d> triangle2(3);
	triangle2[0] = triangle[0].div(40);
	triangle2[1] = triangle[1].div(40);
	triangle2[2] = triangle[2].div(40);
	draw_2d_triangles({ triangle2 });
	cout << "test complete\n";
}
*/

Model3d cube(Vec3d p1, Vec3d p2, PointsList* pl) {
	vector<Vec3d> points = { p1, p1, p1, p1, p2, p2, p2, p2 };
	points[1].x = p2.x;
	points[2].y = p2.y;
	points[3].x = p2.x; points[3].y = p2.y;
	points[4].x = p1.x; points[4].y = p1.y;
	points[5].y = p1.y;
	points[6].x = p1.x;
	return Model3d({ Triangle3d(points[0], points[1], points[2], pl) ,
					 Triangle3d(points[1], points[2], points[3], pl),
					 Triangle3d(points[1], points[5], points[7], pl),
		             Triangle3d(points[1], points[7], points[3], pl),
					 Triangle3d(points[5], points[4], points[6], pl),
					 Triangle3d(points[5], points[6], points[7], pl),
					 Triangle3d(points[4], points[5], points[1], pl),
					 Triangle3d(points[4], points[1], points[0], pl), 
					 Triangle3d(points[2], points[3], points[7], pl),
					 Triangle3d(points[2], points[7], points[6], pl), 
					 Triangle3d(points[4], points[0], points[2], pl),
					 Triangle3d(points[4], points[2], points[6], pl), });
}

Camera init_cam(View view) {
	Camera res(Vec3d(0, 0, 0), 0, 0, 0);
	res.set_aspect_ratio(view.get_aspect_ratio());
	return res;
}

#define SDL_main main

int main(int argc, const char** argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	context.setAsDefaultForAssertsOutOfTestCases();
	if (context.shouldExit()) return test_result;

	PointsList points_list;
	View view{};
	Camera cam = init_cam(view);
	vector<Model3d> models3d = { cube(Vec3d(-1, -1, 3), Vec3d(1, 1, 5), &points_list) };

	//game loop
	do {
		points_list.reset_points();
		for (int i = 0; i < models3d.size(); i++) {
			models3d[i].remove_behind(cam);
			models3d[i].put_points_in_list();
		}
		points_list.project_points(cam);
		for (Model3d& model : models3d) {
			model.set_triangles_projected();
			model.remove_not_visible2d();
		}
		vector<vector<Vec2d>> triangles_to_draw(0);
		vector<vector<Vec2d>> added_triangles;
		for (int i = 0; i < models3d.size(); i++) {
			added_triangles = models3d[i].get_draw_points();
			triangles_to_draw.insert(triangles_to_draw.begin(), added_triangles.begin(), added_triangles.end());
		}
		try {
			view.draw_2d_triangles(triangles_to_draw);
		}
		catch (runtime_error error) {
			cout << error.what() << endl;
		}
		view.inputsUpdate();
		cam.rotate(-view.YCamRotation(), 1);
		cam.rotate(view.XCamRotation(), 0);
		cam.move(cam.dir * view.forwardMove() + 
			cam.dir.rotate(PI / 2, 1) * view.rightMove() + 
			Vec3d(0, -view.upMove(), 0));
	} while (not view.exit());
	return 0;
}
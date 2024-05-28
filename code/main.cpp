#define SDL_main main

#include <Engine3d/3dEngine.hpp>
#include <Engine4d/4dEngine.hpp>


int main(int argc, const char** argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	context.setAsDefaultForAssertsOutOfTestCases();
	if (context.shouldExit()) return test_result;

	View view{};
	Engine4d engine{ {hypercube(Vec4d(-1, -1, 3, -1), Vec4d(1, 1, 5, 1))} , view};
	//Vec3d(-1, -1, 3), Vec3d(1, 1, 5)
	
	do {
		view.inputsUpdate();
		engine.rotate(-view.YCamRotation(), 1);
		engine.rotate(view.XCamRotation(), 3);
		engine.move(engine.getDir() * view.forwardMove() +
			engine.getDir().rotation(PI / 2, 0, 2) * view.rightMove() +
			Vec4d(0, -view.upMove(), 0, 0));
		view.draw_2d_triangles(engine.triangles_to_draw());
	} while (not view.exit());
	return 0;
}
#include "graphics\Window.h"
#include "utils\OBJLoader.h"
#include "graphics\Renderable.h"
#include "graphics\renderers\StaticRenderer.h"
#include "math\Math.h"
#include <iostream>

void run();

int main(int argc, char *argv[])
{
	run();

	//system("PAUSE");

	return 0;
}

void run() {

	Window window("LoreEngine3D", 1280, 720, DISPLAY_WINDOWED, false, true);
	window.create().center().focus();

	Camera* camera = new Camera(Vector3f(0, 0, -10.0f), Vector3f(0), PROJECTION_PERSPECTIVE, window.getWidth(), window.getHeight());
	Shader* shader = new Shader("res/shaders/default.vs", "res/shaders/default.fs");

	StaticRenderer renderer(camera, shader);

	Mesh* mesh = loadMesh("res/meshes/cube.obj");

	Renderable* renderable = new Renderable(mesh, Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(1, 1, 1));

	while (true) {

		if (window.shouldClose()) break;

		window.clear();

		renderer.submit(*renderable);
		renderer.flush();

		window.update();
	}

	window.dispose();
	glfwTerminate();

	//delete mesh;
	//delete renderable;

}
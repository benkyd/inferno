#include "../src/inferno.hpp"

static const int width = 1000;
static const int height = 1000;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	inferno.InitWindow(width, height);

	Scene* scene = new Scene(width, height);
	scene->sky = new SolidColourSky({ 0.0f, 0.0f, 0.0f } 0.0f);
	scene->camera = new Camera(width, height);

	// Light
	Sphere light({ 35.0f, 56.0f, 25.0f }, 35.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f));
	scene->objects.push_back(&light);

	Sphere sphere({ 0.0f, 0.0f, -8.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere);

	Plane plane({ 0.0f,-1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.9f, 0.9f, 0.9f }, 0.0f));
	scene->objects.push_back(&plane);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

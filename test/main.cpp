#include <iostream>

#include "../src/inferno.hpp"

static const int width = 700;
static const int height = 700;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	bool status = inferno.InitWindow(width, height);

	if (!status) {
		std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
	}

	Scene* scene = new Scene(width, height);

	scene->sky = new GradientSky({ 35.0f / 255.0f, 148.0f / 255.0f, 235.0f / 255.0f }, { 1.0f, 1.0f, 1.0f }, 3.0f);;

	scene->camera = new Camera(width, height);

	scene->objects.push_back(new Sphere({ -2.1f, 0.0f, -8.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.0f, 0.0f, 0.0f, 0.0f, false, false)));
	scene->objects.push_back(new Sphere({ 0.0f, 0.0f, -8.0f }, 1.0f, new GlossyMaterial({ 0.817f, 0.374, 0.574 }, 0.7f, fastDegreetoRadian(30.0f))));
	scene->objects.push_back(new Sphere({ 2.1f, 0.0f, -8.0f }, 1.0f, new GlossyMaterial({ 0.817f, 0.374, 0.574 }, 0.7f, fastDegreetoRadian(60.0f))));

	scene->objects.push_back(new Sphere({ 35.0f, 50.0f, 25.0f }, 25.0f, new Light({ 1.0f, 1.0f, 1.0f }, 100.0f)));

	scene->objects.push_back(new Plane({ 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.2f, 0.2f, 0.2f }, 0.0f, 0.0f, 1.5f, 0.0f, false, false)));

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

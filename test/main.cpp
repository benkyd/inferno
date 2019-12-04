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

	scene->objects.push_back(new Sphere({ 0.0f, 0.0f, -6.0f }, 1.0f, new MatteMaterial({ 0.2f, 0.2f, 0.2f })));
	scene->objects.push_back(new Sphere({ -5.0f, -5.0f, -1.0f }, 1.0f, new Light({ 0.2f, 0.2f, 0.2f }, 5.0f)));

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

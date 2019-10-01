#include <iostream>

#include "../src/inferno.hpp"

static const int width = 1000;
static const int height = 1000;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	bool status = inferno.InitWindow(width, height);

	if (!status) {
		std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
	}

	Scene* scene = new Scene(width, height);

	Sky* sky = new GradientSky({ 35.0f / 255.0f, 148.0f / 255.0f, 235.0f / 255.0f }, { 1.0f, 1.0f, 1.0f }, 5.0f);
	scene->sky = sky;

	scene->camera = new Camera(width, height);
	
	//Sphere sphere1({ 1.3f, -0.8f, -5.0f }, 0.2f, new Material({ 0.817f, 0.374, 0.574 }));
	//scene->objects.push_back(&sphere1);

	Sphere sphere({ -2.1f, 0.0f, -8.0f }, 1.0f, new GlossyMaterial({ 0.817f, 0.374, 0.574 }, 0.5f, fastDegreetoRadian(0.0f)));
	scene->objects.push_back(&sphere);
	Sphere sphere1({ 0.0f, 0.0f, -8.0f }, 1.0f, new GlossyMaterial({ 0.817f, 0.374, 0.574 }, 0.5f, fastDegreetoRadian(3.0f)));
	scene->objects.push_back(&sphere1);
	Sphere sphere2({ 2.1f, 0.0f, -8.0f }, 1.0f, new GlossyMaterial({ 0.817f, 0.374, 0.574 }, 0.5f, fastDegreetoRadian(30.0f)));
	scene->objects.push_back(&sphere2);

	Sphere light({ 35.0f, 50.0f, 25.0f }, 25.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 200.0f));
	scene->objects.push_back(&light);

	Plane plane({ 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.2f, 0.2f, 0.2f }));
	scene->objects.push_back(&plane);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

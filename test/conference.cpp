#include <iostream>

#include "../src/inferno.hpp"

static const int width = 1000;
static const int height = 1000;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	inferno.InitWindow(width, height);

	Scene* scene = new Scene(width, height);
	scene->camera = new Camera(width, height);

	scene->sky = new SolidSky({ 0.0f, 0.0f, 0.0f }, 0.0f);
	
	scene->objects.push_back(new Sphere({ 5000.0f, 1700.0f, 25.0f }, 1000.0f, new Light({ 1.0f, 1.0f, 1.0f }, 1000.0f)));

	std::string models     = RESOURCES + std::string("//models//"); 	
	std::string conference = RESOURCES + std::string("//models//conference.obj");

	std::vector<Triangle*> tris1 = LoadTrianglesBasic(conference, models);

	Mesh* mesh1 = new Mesh(tris1);
	mesh1->Translate({ 0.0f, 1.6f, 0.0f });
    mesh1->Optimise();
	scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

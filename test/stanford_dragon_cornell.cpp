#include <iostream>

#include "../src/inferno.hpp"

static const int width = 600;
static const int height = 600;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	inferno.InitWindow(width, height);

	Scene* scene = new Scene(width, height);
	scene->camera = new Camera(width, height);

	Sky* sky = new SolidSky({ 0.0f, 0.0f, 0.0f }, 0.0f);
	scene->sky = sky;

	Sphere* sphere = new Sphere({ -0.302, -0.385999, -3.74202 }, 0.03f, new Material({ 0.345f, 0.133f, 0.050f }, 300.0f, 0.0f, 0.0f, 0.0f, false, true));
	scene->objects.push_back(sphere);

	std::string models  = RESOURCES + std::string("//models//"); 	
	std::string dragon  = RESOURCES + std::string("//models//dragon-cornell-size.obj");
	std::string cornell = RESOURCES + std::string("//models//cornell-box.obj");

	// Material* mat = new GlossyMaterial({ 1.0f, 1.0f, 1.0f }, 0.2f, fastDegreetoRadian(30.0f));
	// Material* mat = new MatteMaterial({ 1.0f, 1.0f, 1.0f });
	// std::vector<Triangle*> tris = LoadTrianglesBasic(dragon, models, mat);

	// Mesh* mesh = new Mesh(tris);
	// mesh->Translate({ 0.01f, -1.0, -3.6f });
	// mesh->Optimise();
	// scene->meshs.push_back(mesh);

	std::vector<Triangle*> tris1 = LoadTrianglesBasic(cornell, models);

	Mesh* mesh1 = new Mesh(tris1);
	mesh1->Translate({ 0.01f, -1.0, -3.6f });
	scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

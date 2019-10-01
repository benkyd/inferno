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

	//Sphere* sphere = new Sphere({ -0.302, -0.385999, -3.74202 }, 0.03f, new Material({ 0.345f, 0.133f, 0.050f }, 300.0f, 0.0f, 0.0f, 0.0f, false, true));
	//scene->objects.push_back(sphere);

	Plane* plane = new Plane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 0.0f, 0.0f, 0.0f, false, false));
	scene->objects.push_back(plane);

	Material* mat = new GlossyMaterial({ 1.3f, 1.3f, 1.3f }, 0.2f, fastDegreetoRadian(30.0f));
	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//models//dragon-cornell-size.obj", "E://Projects//Inferno//resources//models", mat);
	// std::vector<Triangle*> tris = LoadTrianglesBasic("/home/ben/programming/inferno/resources/models/dragon-cornell-size.obj", "/home/ben/programming/inferno/resources/models/", mat);

	Sphere* sphere = new Sphere({ 0.0f, -0.6f, -4.0f }, 0.4f, mat);
	scene->objects.push_back(sphere);

	//Mesh* mesh = new Mesh(tris);
	//mesh->Translate({ 0.01f, -1.0, -3.6f });
	//mesh->Optimise();
	//scene->meshs.push_back(mesh);

	std::vector<Triangle*> tris1 = LoadTrianglesBasic("E://Projects//Inferno//resources//models//cornell-box.obj", "E://Projects//Inferno//resources//models//");
	//std::vector<Triangle*> tris1 = LoadTrianglesBasic("/home/ben/programming/inferno/resources/models/cornell-box.obj", "/home/ben/programming/inferno/resources/models/");

	Mesh* mesh1 = new Mesh(tris1);
	mesh1->Translate({ 0.01f, -1.0, -3.6f });
	scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

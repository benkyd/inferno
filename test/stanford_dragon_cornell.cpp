#include <iostream>

#include "../src/inferno.hpp"

static const int width = 2000;
static const int height = 2000;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	inferno.InitWindow(width, height);

	Scene* scene = new Scene(width, height);
	scene->camera = new Camera(width, height);

	Sky* sky = new SolidSky({ 0.0f, 0.0f, 0.0f }, 0.0f);
	scene->sky = sky;

	Plane* plane = new Plane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 0.0f, 0.0f, 0.0f, false, false));
	scene->objects.push_back(plane);

	Material* mat = new GlossyMaterial({ 1.3f, 1.3f, 1.3f }, 0.2f, fastDegreetoRadian(30.0f));
	std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//models//dragon-cornell-size.obj", "E://Projects//Inferno//resources//models", mat);
	// std::vector<Triangle*> tris = LoadTrianglesBasic("/home/ben/programming/inferno/resources/models/dragon-cornell-size.obj", "/home/ben/programming/inferno/resources/models/", mat);

	Mesh* mesh = new Mesh(tris);
	mesh->Translate({ 0.01f, -1.0, -3.6f });
	mesh->Optimise();
	scene->meshs.push_back(mesh);

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

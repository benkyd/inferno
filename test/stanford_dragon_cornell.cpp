#include <iostream>

#include "../src/inferno.hpp"

static const int width = 500;
static const int height = 500;

int main(int argc, char** argv) {
	InfernoEngine inferno;

	inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

	inferno.InitWindow(width, height);

	Scene* scene = new Scene(width, height);
	scene->camera = new Camera(width, height);

	Sky* sky = new SolidSky({ 0.0f, 0.0f, 0.0f }, 0.0f);
	scene->sky = sky;

	Material* mat = new GlossyMaterial({ 1.2f, 1.2f, 1.2f }, 0.1f, fastDegreetoRadian(20.0f));
	// std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//models//dragon-cornell-size.obj", "E://Projects//Inferno//resources//models", mat);
	// std::vector<Triangle*> tris = LoadTrianglesBasic("/home/ben/programming/inferno/resources/models/dragon-cornell-size.obj", "/home/ben/programming/inferno/resources/models/", mat);

	Sphere sphere1({ 0.0f, -0.6f, -4.0f }, 0.4f, mat);
	scene->objects.push_back(&sphere1);

	// Mesh* mesh = new Mesh(tris);
	// mesh->Translate({ 0.01f, -1.0, -3.6f });
	// mesh->Optimise();
	// scene->meshs.push_back(mesh);

	// std::vector<Triangle*> tris1 = LoadTrianglesBasic("E://Projects//Inferno//resources//models//cornell-box.obj", "E://Projects//Inferno//resources//models//");
	std::vector<Triangle*> tris1 = LoadTrianglesBasic("/home/ben/programming/inferno/resources/models/cornell-box.obj", "/home/ben/programming/inferno/resources/models/");

	Mesh* mesh1 = new Mesh(tris1);
	mesh1->Translate({ 0.01f, -1.0, -3.6f });
	scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

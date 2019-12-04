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

	Sky* sky = new SolidSky({ 0.0f, 0.0f, 0.0f }, 0.0f);
	scene->sky = sky;

	// Material* mat = new GlossyMaterial({ 1.0f, 1.0f, 1.0f }, 0.2f, fastDegreetoRadian(30.0f));
	Material* mat = new MatteMaterial({ 1.0f, 1.0f, 1.0f });

	std::string models =  RESOURCES + std::string("//models//"); 	
	std::string lucy =    RESOURCES + std::string("//models//lucy.obj");
	std::string cornell = RESOURCES + std::string("//models//cornell-box.obj");

	std::vector<Triangle*> tris = LoadTrianglesBasic( lucy, models, mat);

	Mesh* mesh = new Mesh(tris);
	mesh->Translate({ -0.05f, -1.01, -3.8f });
	mesh->Optimise();
	scene->meshs.push_back(mesh);

	std::vector<Triangle*> tris1 = LoadTrianglesBasic(cornell, models);

	Mesh* mesh1 = new Mesh(tris1);
	mesh1->Translate({ 0.01f, -1.0, -3.6f });
	scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

	inferno.Ready();
	inferno.Render();

	return 0;
}

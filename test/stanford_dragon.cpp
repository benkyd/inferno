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

	Sky* sky = new GradientSky({ 35.0f / 255.0f, 148.0f / 255.0f, 235.0f / 255.0f }, { 1.0f, 1.0f, 1.0f }, 4.0f);
	scene->sky = sky;

	Sphere* sun = new Sphere({ 35.0f, 50.0f, 25.0f }, 25.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 100.0f));
	scene->objects.push_back(sun);

	Sphere* mouthLight = new Sphere({ -0.457001f, 0.19f, -3.53899f }, 0.02f, new Material({ 1.0f, 0.9f, 0.8f }, 0.0f, 500.0f));
	scene->objects.push_back(mouthLight);

	Plane* plane = new Plane({ 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.847f, 0.792f, 0.658f }, 0.2f));
	scene->objects.push_back(plane);

	Material* mat = new GlossyMaterial({ 0.717f, 0.792f, 0.474 }, 0.5f, fastDegreetoRadian(20.0f));
	std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//models//dragon.obj", "E://Projects//Inferno//models//resources", mat);
	// std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//dragon-normals.obj", "//home//ben//programming//inferno//resources//resources");

    Mesh* mesh1 = new Mesh(tris);
	mesh1->Translate({ 0.2f, -1.04, -3.8f });
    mesh1->Optimise();
    scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();

	return 0;
}

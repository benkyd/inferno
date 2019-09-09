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

	scene->objects.push_back(new Sphere({ 35.0f, 26.0f, 25.0f }, 15.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f)));
	scene->objects.push_back(new Sphere({-0.457001f, 0.19f, -3.53899f}, 0.02f,  new Material({ 1.0f, 0.9f, 0.8f }, 0.0f, 500.0f)));
	scene->objects.push_back(new Plane( { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.847f, 0.792f, 0.658f }, 0.2f)));

	std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//dragon-normals.obj", "E://Projects//Inferno//resources");
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
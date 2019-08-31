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
    scene->camera = new Camera(width, height);
    
	//scene->objects.push_back(new Sphere({  0.0f, 0.0f, -4.0f }, 1.0f));
	//scene->objects.push_back(new Sphere({  2.0f, 0.0f, -8.0f }, 1.0f));
	//scene->objects.push_back(new Sphere({ -2.0f, 0.0f, -8.0f }, 1.0f));
	//scene->objects.push_back(new Plane( { 0.0f, -25.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }));

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//dragon-normals.obj", "E://Projects//Inferno//resources");
    //for (const auto& object : tris)
  	//    object->Translate({ 0.0f, -5.0f, -20.0f });

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//lucy-normals.obj", "E://Projects//Inferno//resources");
    //for (const auto& object : tris)
	//    object->Translate({ 0.0f, -3.9f, -10.6f });

	std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//cornell.obj", "E://Projects//Inferno//resources");
    for (const auto& object : tris)
		object->Translate({ 0.0f, -0.9f, -3.0f });

    Mesh* mesh = new Mesh(tris);
    mesh->Optimise();
    scene->meshs.push_back(mesh);

	inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();

	return 0;
}

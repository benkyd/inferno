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
    
	scene->objects.push_back(new Sphere({ 0.6f, 0.0f, -3.5f }, 0.5f, new Material({ 1.0f, .5f, .5f }, 0.3f)));
	//scene->objects.push_back(new Sphere({  0.0f, 0.0f, -8.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.7f)));
	//scene->objects.push_back(new Sphere({  2.0f, 0.0f, -6.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f)));
	//scene->objects.push_back(new Sphere({ -2.0f, 0.0f, -9.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f)));
	//scene->objects.push_back(new Plane( { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 1.0f, 1.0f, 0.0f }, .3f)));

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//dragon-normals.obj", "E://Projects//Inferno//resources");
    //for (const auto& object : tris)
  	//    object->Translate({ 0.0f, -5.0f, -20.0f });

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//lucy-normals.obj", "E://Projects//Inferno//resources");

	//Mesh* mesh = new Mesh(tris);
	//mesh->Translate({ 0.0f, -1.01f, -3.0f });
	//mesh->Optimise();
	//scene->meshs.push_back(mesh);

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//cornell-box.obj", "E://Projects//Inferno//resources");
	std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//cornell.obj", "E://Projects//Inferno//resources");

    Mesh* mesh1 = new Mesh(tris);
	mesh1->Translate({ 0.0f, -1.0f, -3.0f });
    mesh1->Optimise();
    scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();

	return 0;
}

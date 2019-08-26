#include <iostream>
#include "../src/inferno.hpp"

static const int width = 600;
static const int height = 600;

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_PROGRESSIVE_GUI);

    bool status = inferno.InitWindow(width, height);
    if (!status) {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }

    Scene* scene = new Scene(width, height);
    scene->camera = new Camera(width, height);
    
    // scene->objects.push_back(new Sphere({0.0f, 0.0f, -4.0f}, 1.0f));

    // std::vector<Triangle*> tris = LoadTrianglesBasic("/home/ben/programming/inferno/resources/dragon-normals.obj");
    // for (const auto& object : tris)
  	//     object->Translate({ 0.0f, -5.0f, -20.0f });

	// std::vector<Triangle*> tris = LoadTrianglesBasic("/home/ben/programming/inferno/resources/lucy-normals.obj");
	// std::vector<Triangle*> tris = LoadTrianglesBasic("E:/Projects/Inferno/resources/lucy-normals.obj");
    // for (const auto& object : tris)
	//     object->Translate({ 0.0f, -3.9f, -10.6f });

	//std::vector<Triangle*> tris = LoadTrianglesBasic("/home/ben/programming/inferno/resources/cornell.obj");
	std::vector<Triangle*> tris = LoadTrianglesBasic("E:/Projects/Inferno/resources/cornell.obj");
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

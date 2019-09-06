#include <iostream>

#include "../src/inferno.hpp"

static const int width = 700;
static const int height = 700;

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

    bool status = inferno.InitWindow(width, height);
    if (!status) {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }

    Scene* scene = new Scene(width, height);
    scene->camera = new Camera(width, height);
    
	// scene->objects.push_back(new Sphere({  0.0f, 0.0f, -8.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.7f)));
	// scene->objects.push_back(new Sphere({  2.0f, 0.0f, -6.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f)));
	// scene->objects.push_back(new Sphere({ -2.0f, 0.0f, -9.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f)));
	scene->objects.push_back(new Sphere({ 5.0f, 6.0f, 9.0f }, 5.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f)));
	scene->objects.push_back(new Plane( { 0.0f,-1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 1.0f, 0.9f, 0.9f }, 0.1f)));
	// scene->objects.push_back(new Plane( { 0.0f, 10.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, new Material({ 1.0f, 0.9f, 0.9f }, 0.0f, 1.0f)));

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//dragon-normals.obj", "E://Projects//Inferno//resources");
	// std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//dragon-normals.obj", "//home//ben//programming//inferno//resources//resources");
    // for (const auto& object : tris)
  	//    object->Translate({ 0.0f, -5.0f, -20.0f });

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//lucy-normals.obj", "E://Projects//Inferno//resources");
	std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//lucy-normals.obj", "//home//ben//programming//inferno//resources//resources");

	//Mesh* mesh = new Mesh(tris);
	//mesh->Translate({ 0.0f, -1.01f, -3.0f });
	//mesh->Optimise();
	//scene->meshs.push_back(mesh);

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//cornell-box.obj", "E://Projects//Inferno//resources");
	// std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//cornell.obj", "//home//ben//programming//inferno//resources//resources");

    Mesh* mesh1 = new Mesh(tris);
	mesh1->Translate({ 0.0f, -1.0f, -3.0f });
    mesh1->Optimise();
    scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();

	return 0;
}

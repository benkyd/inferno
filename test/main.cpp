#include <iostream>

#include "../src/inferno.hpp"

static const int width = 300;
static const int height = 300;

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

    bool status = inferno.InitWindow(width, height);

    if (!status) {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }

    Scene* scene = new Scene(width, height);
    scene->camera = new Camera(width, height);

	scene->objects.push_back(new Sphere({ 0.0f, 0.0f, -4.0f }, 1.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f)));
	scene->objects.push_back(new Sphere({ 35.0f, 26.0f, 25.0f }, 15.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f)));
	scene->objects.push_back(new Plane( { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.847f, 0.792f, 0.658f }, 0.2f)));

	// std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//dragon-normals.obj", "E://Projects//Inferno//resources");
	// std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//dragon-normals.obj", "//home//ben//programming//inferno//resources//resources");

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//lucy-normals-larger.obj", "E://Projects//Inferno//resources");
	//std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//lucy-normals.obj", "//home//ben//programming//inferno//resources//resources");

	//Mesh* mesh = new Mesh(tris);
	//mesh->Translate({ 0.0f, -1.01f, -3.0f });
	//mesh->Optimise();
	//scene->meshs.push_back(mesh);

	//std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//box.obj", "E://Projects//Inferno//resources");
	//std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//cornell.obj", "//home//ben//programming//inferno//resources//resources");

    // Mesh* mesh1 = new Mesh(tris);
	// mesh1->Translate({ 0.2f, -1.04, -3.8f });
    // mesh1->Optimise();
    // scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();

	return 0;
}

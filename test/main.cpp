#include <iostream>

#include "../src/inferno.hpp"

static const int width = 1010;
static const int height = 1010;

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

    bool status = inferno.InitWindow(width, height);

    if (!status) {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }

    Scene* scene = new Scene(width, height);
    scene->camera = new Camera(width, height);
	
	Sphere sphere({ 0.0f, 0.0f, -20.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere);

	Sphere sphere1({ 0.0f, 0.0f, -20.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere1);

	Sphere sphere2({ -3.0f, 1.0f, -10.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere2);

	Sphere sphere3({ 6.0f, 3.0f, -13.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere3);

	Sphere sphere4({ -1.0f, 2.0f, -10.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere4);

	Sphere sphere5({ 2.0f, 5.0f, -15.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
	scene->objects.push_back(&sphere5);

	Sphere light({ 35.0f, 56.0f, 25.0f }, 35.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f));
	scene->objects.push_back(&light);

	Plane plane({ 0.0f,-1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.9f, 0.9f, 0.9f }, 0.0f));
	scene->objects.push_back(&plane);

	//scene->objects.push_back(new Sphere({ 35.0f, 26.0f, 25.0f }, 15.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f)));
	//scene->objects.push_back(new Sphere({-0.457001f, 0.19f, -3.53899f}, 0.02f,  new Material({ 1.0f, 0.9f, 0.8f }, 0.0f, 500.0f)));
	//scene->objects.push_back(new Plane( { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.847f, 0.792f, 0.658f }, 0.2f)));

	// std::vector<Triangle*> tris = LoadTrianglesBasic("E://Projects//Inferno//resources//dragon-normals.obj", "E://Projects//Inferno//resources");
	//std::vector<Triangle*> tris = LoadTrianglesBasic("//home//ben//programming//inferno//resources//dragon-normals.obj", "//home//ben//programming//inferno//resources//resources");

    //Mesh* mesh1 = new Mesh(tris);
	//mesh1->Translate({ 0.2f, -1.04, -3.8f });
    //mesh1->Optimise();
    //scene->meshs.push_back(mesh1);

	inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();

	return 0;
}

#include <iostream>
#include "../src/inferno.hpp"

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_PROGRESSIVE_GUI);

    bool status = inferno.InitWindow(600, 600);
    if (!status) {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }

    Scene* scene = new Scene(600, 600);
    scene->camera = new Camera(600, 600);
    scene->objects.push_back(new Plane({0.0f, -0.5f, 0.0f}, {0.0f, -1.0f, 0.0f}));
    scene->objects.push_back(new Sphere({0.0f, 0.0f, -4.0f}, 1.0f));
    scene->objects.push_back(new Triangle({ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f }, { -1.0f, 1.0f, 0.0f }, { 1.0f, -1.0f ,0.0f }, { 0.25f, 0.75f, 0.75f }, { 0.0f, 0.0f, 0.0f }));

    inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();
}

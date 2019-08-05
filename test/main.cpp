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
    scene->objects.push_back(new Plane({0.0f, -0.5f, 0.0f}, {0.0f, -1.0f, 0.0f}));
    scene->objects.push_back(new Sphere({0.0f, 0.0f, -4.0f}, 1.0f));

    inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();
}

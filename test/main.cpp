#include <iostream>
#include "../src/inferno.hpp"

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_PROGRESSIVE_GUI);

    bool status = inferno.InitWindow(600, 600);
    if (!status) {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }

    Scene* scene = new Scene();
    scene->camera = new Camera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, 600, 600);

    inferno.SetScene(scene);

    inferno.Ready();
    inferno.Render();
}

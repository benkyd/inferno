#include <iostream>
#include "../src/inferno.hpp"

int main(int argc, char** argv) {
    InfernoEngine inferno;

    inferno.SetMode(MODE_PROGRESSIVE_GUI);
    bool status = inferno.InitWindow();
    if (!status {
        std::cout << "Error initializing window: " << inferno.LastError() << std::endl;
    }


}

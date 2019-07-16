#ifndef INFERNO_INFERNO_H_
#define INFERNO_INFERNO_H_

#include <string>

class Display;

enum OperationMode {
    MODE_PROGRESSIVE_GUI,
    MODE_PROGRESSIVE_IMG,
    MODE_SAMPLES_IMG
};

// General idea is that the rendering stays the same (Other than progressive / sampling)
// and the renderer passes a full framebuffer (different depending on mode) to either the
// display or an image generator, undecided how this will work but it will make for some
// interesting features, ImGui can be used for settings inside the progressive mode gui

class InfernoEngine {
public:

    void SetMode(OperationMode mode);

    // Initializes the SDL framebuffer with OpenGL
    bool InitWindow();

    // Queries the modules, if one of them errored it finds their error string
    // and returns it to the main execution code
    std::string LastError();

private:

    OperationMode m_mode = MODE_PROGRESSIVE_GUI; 

    // Gotta be a pointer so that if the display
    // mode is not selected then it is nothing
    Display* m_display = nullptr;

};

#endif

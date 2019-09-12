#ifndef INFERNO_INFERNO_H_
#define INFERNO_INFERNO_H_

#include <string>
#include <vector>
#include <utility>

#include "common.hpp"

// Give the user access to the base classes to define shit
#include "util/assetloader.hpp"

#include "definitions/scene.hpp"
#include "definitions/camera.hpp"

#include "definitions/primatives/mesh.hpp"
#include "definitions/primatives/sphere.hpp"
#include "definitions/primatives/plane.hpp"
#include "definitions/primatives/triangle.hpp"

#include "definitions/materials/material.hpp"
#include "definitions/materials/texture.hpp"

class Display;
class Renderer;

// General idea is that the rendering stays the same (Other than progressive / sampling)
// and the renderer passes a full framebuffer (different depending on mode) to either the
// display or an image generator, undecided how this will work but it will make for some
// interesting features, ImGui can be used for settings inside the progressive mode gui
class InfernoEngine {
public:
    InfernoEngine();

    void SetMode(OperationMode mode);

    // Initializes the SDL framebuffer with OpenGL
    bool InitWindow(int xRes, int yRes);

    // Functions related to raytracing
    void SetScene(Scene* scene);

    void Ready();
    void Render();

    // Queries the modules, if one of them errored it finds their error string
    // and returns it to the main execution code, the same happens for warnings
    // each module class should have an "err" and "warn" a string, timestamp 
    // pair as an atribute
    std::string LastError();
    std::string LastWarn();

    // Error and warning
    // std::pair<std::string, int>  err;
    // std::pair<std::string, int> warn;

    virtual ~InfernoEngine();
private:

    OperationMode m_mode = MODE_OPERATION_PROGRESSIVE_GUI; 

    // Initialized flag - core engine features can't
    // be changed while this flag is set to true
    bool m_initialized = false;

    // Gotta be a pointer so that if the display
    // mode is not selected then it is nothing
    Display* m_display = nullptr;
    Renderer* m_renderer = nullptr;

    Scene* m_scene = nullptr;
};

#endif

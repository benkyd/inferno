#include "progressiverenderer.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"

ProgressiveRenderer::ProgressiveRenderer() {
    
}

void ProgressiveRenderer::Init(DisplayInterface* interface, Scene* scene) {
    m_interface = interface;
    m_scene = scene;
}

void ProgressiveRenderer::Render() {
    // RENDERING CAN ACTUALLY START

    while (m_interface->Active) {

        // Take input
        SDL_Event e;
        while (SDL_PollEvent(&e) == SDL_TRUE) 
            if (e.type == SDL_QUIT) m_interface->Close();

        // Update the camera
        m_scene->camera->Update();
        
        for (int x = 0; x < m_scene->w; x++)
        for (int y = 0; y < m_scene->h; y++) {
            
        }

        // Swap framebuffers
        m_interface->Update();
    }
}

#include "./progressiverenderer.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

ProgressiveRenderer::ProgressiveRenderer() {
    
}

void ProgressiveRenderer::Init(DisplayInterface* interface) {
    m_interface = interface;
}

void ProgressiveRenderer::Render() {
    // RENDERING CAN ACTUALLY START

    while (m_interface->Active) {
        SDL_Event e;
        while (SDL_PollEvent(&e) == SDL_TRUE) 
            if (e.type == SDL_QUIT) m_interface->Close();
        
        for (int i = 0; i < 360000; i++) {
            m_interface->SetPixelSafe(rand() % m_interface->XRes,
                                    rand() % m_interface->YRes,
                                    rgb888(rand() % 255, rand() % 255, rand() % 255));
        }

        m_interface->Update();
    }
}
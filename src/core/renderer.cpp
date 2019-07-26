#include "../display/display.hpp"
#include "../pixel.hpp"
#include "./renderer.hpp"

Renderer::Renderer(OperationMode mode) {
    m_mode = mode;
}

void Renderer::SetMode(OperationMode mode, int samples) {
    m_mode = mode;
    m_samples = samples;
}

void Renderer::Render() {
    if (m_mode == MODE_PROGRESSIVE_GUI || m_mode == MODE_PROGRESSIVE_IMG) {
        RenderProgressive();
    } else if (m_mode == MODE_SAMPLES_IMG) {
        RenderSamples();
    } else {
        // Add an error & return
    }
}

void Renderer::Render(uint32_t* framebuffer) {
    m_framebuffer = framebuffer;
    if (m_mode == MODE_PROGRESSIVE_GUI || m_mode == MODE_PROGRESSIVE_IMG) {
        RenderProgressive();
    } else if (m_mode == MODE_SAMPLES_IMG) {
        RenderSamples();
    } else {
        // Add an error & return
    }
}

void Renderer::Init() {

}

void Renderer::Init(DisplayInterface* display) {
    // Add warning
    if (!display) return;
    if(!m_framebuffer) {
        m_framebuffer = display->Framebuffer;
    }
    m_interface = display;
}

void Renderer::RenderProgressive() {
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

void Renderer::RenderSamples() {

}

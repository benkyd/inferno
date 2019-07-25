#include "../display/display.hpp"
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

void Renderer::Init(Display* display) {
    // Add warning
    if (!display) return;
    m_framebuffer = display->Framebuffer;
}

void Renderer::RenderProgressive() {

}

void Renderer::RenderSamples() {

}

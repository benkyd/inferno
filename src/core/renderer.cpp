#include "../display/display.hpp"
#include "../pixel.hpp"
#include "./renderer.hpp"

#include "../engine/progressiverenderer.hpp"

Renderer::Renderer(OperationMode mode) {
    m_mode = mode;
}

void Renderer::SetMode(OperationMode mode, int samples) {
    m_mode = mode;
    m_samples = samples;
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

void Renderer::InitRender(Scene* scene) {
    m_scene = scene;
    RendererInitialized = true;
}

void Renderer::Render() {
    if (!RendererInitialized) return;
    if (m_mode == MODE_PROGRESSIVE_GUI || m_mode == MODE_PROGRESSIVE_IMG) {
        RenderProgressive();
    } else if (m_mode == MODE_SAMPLES_IMG) {
        RenderSamples();
    } else {
        // Add an error & return
    }
}

void Renderer::Render(uint32_t* framebuffer) {
    if (!RendererInitialized) return;
    m_framebuffer = framebuffer;
    if (m_mode == MODE_PROGRESSIVE_GUI || m_mode == MODE_PROGRESSIVE_IMG) {
        RenderProgressive();
    } else if (m_mode == MODE_SAMPLES_IMG) {
        RenderSamples();
    } else {
        // Add an error & return
    }
}

void Renderer::RenderProgressive() {
    m_progressive = new ProgressiveRenderer();
    
    m_progressive->Init(m_interface, m_scene);
    m_progressive->Render();
}

void Renderer::RenderSamples() {

}

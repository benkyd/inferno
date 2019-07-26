#include "inferno.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include "pixel.hpp"

#include "display/display.hpp"
#include "core/renderer.hpp"

InfernoEngine::InfernoEngine() {
    m_initialized = false;
}

void InfernoEngine::SetMode(OperationMode mode) {
    if (!m_initialized) { 
        // warn = 
        return;    
    }
    
    m_mode = mode;
}

bool InfernoEngine::InitWindow(int xRes, int yRes) {
    if (m_initialized) { 
        // warn = 
        return true;    
    }
    
    if (m_display == nullptr)
        m_display = new Display();

    bool status = m_display->InitVideoDisplay("Inferno Engine", xRes, yRes);
    if (!status) {
        return false;
    }

    m_renderer = new Renderer(m_mode);
    if (!m_renderer) {
        return false;
    }
    m_renderer->Init(m_display);

    m_initialized = true;

    return true;
}

void InfernoEngine::Ready() {
    if (!m_initialized) m_initialized = true;
}

void InfernoEngine::Render() {
    m_renderer->Render(m_display->Framebuffer);
}

std::string InfernoEngine::LastError() {
    return "";
}

std::string InfernoEngine::LastWarn() {
    return "";
}

InfernoEngine::~InfernoEngine() {

}

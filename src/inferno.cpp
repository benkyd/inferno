#include "inferno.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include "pixel.hpp"

#include "display/display.hpp"

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

    m_initialized = true;

    return true;
}

void InfernoEngine::Ready() {
    if (!m_initialized) m_initialized = true;
}

void InfernoEngine::Render() {
        while (m_display->WindowOpen) {
        SDL_Event e;
        while (SDL_PollEvent(&e) == SDL_TRUE) 
            if (e.type == SDL_QUIT) m_display->CloseDisplay();
        
        for (int i = 0; i < 360000; i++) {
            m_display->SetPixelSafe(rand() % m_display->XRes,
                                rand() % m_display->YRes,
                                rgb888(rand() % 255, rand() % 255, rand() % 255));
        }

        m_display->Refresh();
    }
}

std::string InfernoEngine::LastError() {
    return "";
}

std::string InfernoEngine::LastWarn() {
    return "";
}

InfernoEngine::~InfernoEngine() {

}

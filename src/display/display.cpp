#include "display.hpp"

#include <iostream>

#include "../pixel.hpp"

Display::Display() 
    : DisplayInterface() {

}

bool Display::Init() {
    return true;
}

bool Display::InitVideoDisplay(std::string title, int x, int y) {
    this->XRes = x; this->YRes = y;

    m_window = SDL_CreateWindow(
        title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        this->XRes * this->Scale, this->YRes * this->Scale,
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!m_window) {
        // Add error
        std::cout << "ERROR: COULD NOT CREATE SDL WINDOW" << std::endl;
        return false;
    }

    this->Active = true;

    m_renderer = SDL_CreateRenderer(
        m_window, -1, SDL_RENDERER_ACCELERATED
    );

    if (!m_renderer) {
        // Add error
        std::cout << "ERROR: COULD NOT CREATE SDL RENDERER" << std::endl;
        return false;    
    }

    m_texture = SDL_CreateTexture(
        m_renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, this->XRes, this->YRes
    );

    if (!m_texture) {
        // Add error
        std::cout << "ERROR: COULD NOT CREATE SDL TEXTURE" << std::endl;
        return false;    
    }

    Framebuffer = (uint32_t*)malloc(this->XRes * this->YRes * sizeof(uint32_t));

    if (!Framebuffer) {
        // Add error
        std::cout << "ERROR: COULD NOT ALLOCATE FRAMEBUFFER" << std::endl;
        return false;    
    }

    return true;
}


void Display::SetPixel(int x, int y, Pixel p) {
    Framebuffer[y * this->XRes + x] = p.rgb();
}

void Display::SetPixel(int x, int y, uint32_t p) {
    Framebuffer[y * this->XRes + x] = p;
}

void Display::SetPixelSafe(int x, int y, Pixel p) {
    if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
        Framebuffer[y * this->XRes + x] = p.rgb();
    }
}

void Display::SetPixelSafe(int x, int y, uint32_t p) {
    if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
        Framebuffer[y * this->XRes + x] = p;
    }
}

void Display::SetFramebuffer(uint32_t* fb) {
    Framebuffer = nullptr;
    Framebuffer = fb;
}

void Display::Update() {
    SDL_UpdateTexture(m_texture, NULL, Framebuffer, this->XRes * sizeof(uint32_t));
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Display::Close() {
    free(Framebuffer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    Active = false;
}

Display::~Display() {

}

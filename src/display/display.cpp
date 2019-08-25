#include "display.hpp"

#include <iostream>

#include "../common.hpp"
#include "../pixel.hpp"

Display::Display() 
    : DisplayInterface() {

}

bool Display::Init() {
    return true;
}

bool Display::InitVideoDisplay(std::string title, int x, int y) {
    this->XRes = x; this->YRes = y;
	Title = title;

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
    memset((void*)Framebuffer, 0, this->XRes * this->YRes * sizeof(uint32_t));
    if (!Framebuffer) {
        // Add error
        std::cout << "ERROR: COULD NOT ALLOCATE FRAMEBUFFER" << std::endl;
        return false;    
    }

    return true;
}

bool Display::InitImGui() {
	ImGui::CreateContext();
	ImGuiSDL::Initialize(m_renderer, XRes, YRes);

	m_imguiTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);

	if (!m_imguiTexture) return false;
	ImGui = true;
	return true;
}

void Display::SetPixel(int x, int y, Pixel p) {
	m_framebufferMutex.lock();
    Framebuffer[y * this->XRes + x] = p.rgb();
	m_framebufferMutex.unlock();
}

void Display::SetPixel(int x, int y, uint32_t p) {
	m_framebufferMutex.lock();
    Framebuffer[y * this->XRes + x] = p;
	m_framebufferMutex.unlock();
}

void Display::SetPixel(int x, int y, glm::vec3 p) {
	Pixel pixel{ (uint8_t)p.x, (uint8_t)p.y, (uint8_t)p.z };
	m_framebufferMutex.lock();
	Framebuffer[y * this->XRes + x] = pixel.rgb();
	m_framebufferMutex.unlock();
}

void Display::SetPixelSafe(int x, int y, Pixel p) {
    if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		m_framebufferMutex.lock();
        Framebuffer[y * this->XRes + x] = p.rgb();
		m_framebufferMutex.unlock();
	}
}

void Display::SetPixelSafe(int x, int y, uint32_t p) {
    if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		m_framebufferMutex.lock();
        Framebuffer[y * this->XRes + x] = p;
		m_framebufferMutex.unlock();
	}
}

void Display::SetPixelSafe(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		Pixel pixel{ (uint8_t)p.x, (uint8_t)p.y, (uint8_t)p.z };
		m_framebufferMutex.lock();
		Framebuffer[y * this->XRes + x] = pixel.rgb();
		m_framebufferMutex.unlock();
	}
}

void Display::SetFramebuffer(uint32_t* fb) {
	m_framebufferMutex.lock();
    Framebuffer = nullptr;
    Framebuffer = fb;
	m_framebufferMutex.unlock();
}

void Display::ClearFramebuffer() {
	m_framebufferMutex.lock();
	memset((void*)Framebuffer, 0, (XRes * YRes) * sizeof(uint32_t));
	m_framebufferMutex.unlock();
}

void Display::Update() {
	ImGuiIO& io = ImGui::GetIO();
	int mouseX, mouseY, wheel = 0;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
	io.DeltaTime = 1.0f / 60.0f;
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);

    SDL_UpdateTexture(m_texture, NULL, Framebuffer, this->XRes * sizeof(uint32_t));
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

    SDL_RenderPresent(m_renderer);
}

void Display::UpdatePartial() {
	SDL_UpdateTexture(m_texture, NULL, Framebuffer, this->XRes * sizeof(uint32_t));
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Display::UpdateTitle(std::string title) {
	Title = title;
	UpdateTitle();
}

void Display::UpdateTitle() {
	SDL_SetWindowTitle(m_window, Title.c_str());
}

void Display::Close() {
    Active = false;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyTexture(m_imguiTexture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    free(Framebuffer);
}

Display::~Display() {

}

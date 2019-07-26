#ifndef INFERNO_DISPLAY_DISPLAY_H_
#define INFERNO_DISPLAY_DISPLAY_H_

#include <SDL2/SDL.h>

#include <string>

#include "./displayinterface.hpp"

class Pixel;

class Display : public DisplayInterface {
public:
    Display();

    bool Init() override;
    bool InitVideoDisplay(std::string title, int x, int y);

    void SetPixel(int x, int y, Pixel p) override;
    void SetPixel(int x, int y, uint32_t p) override;
    void SetPixelSafe(int x, int y, Pixel p) override;
    void SetPixelSafe(int x, int y, uint32_t p) override;

    void SetFramebuffer(uint32_t* fb);

    void Update() override;

    void Close() override;

    virtual ~Display();
private:
    // SDL Internals
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
};

#endif

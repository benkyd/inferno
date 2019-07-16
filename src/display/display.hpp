#ifndef INFERNO_DISPLAY_DISPLAY_H_
#define INFERNO_DISPLAY_DISPLAY_H_

#include <SDL2/SDL.h>

#include <string>

class Pixel;

class Display {
public:
    Display();

    bool InitVideoDisplay(std::string title, int x, int y);

    bool WindowOpen = false;
    int XRes, YRes;
    std::string Title;
    unsigned int Scale = 1;

    void SetPixel(int x, int y, Pixel p);
    void SetPixel(int x, int y, uint32_t p);
    void SetPixelSafe(int x, int y, Pixel p);
    void SetPixelSafe(int x, int y, uint32_t p);

    uint32_t* Framebuffer;
    void SetFramebuffer(uint32_t* fb);

    void Refresh();

    // Error and warn

    void CloseDisplay();

    virtual ~Display();
private:
    // SDL Internals
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

};

#endif

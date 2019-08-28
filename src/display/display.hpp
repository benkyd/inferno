#ifndef INFERNO_DISPLAY_DISPLAY_H_
#define INFERNO_DISPLAY_DISPLAY_H_

#include <mutex>

#include "displayinterface.hpp"

#include "../common.hpp"
#include "../maths.hpp"

class Pixel;

class Display : public DisplayInterface {
public:
    Display();

    bool Init() override;
    bool InitVideoDisplay(std::string title, int x, int y);
	bool InitImGui();

    void Update() override;
	void UpdatePartial() override;
	void UpdateTitle(std::string title) override;
	void UpdateTitle() override;

    void Close() override;

    virtual ~Display();
private:
    // SDL Internals
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
	SDL_Texture* m_imguiTexture;
	std::mutex m_framebufferMutex;
};

#endif

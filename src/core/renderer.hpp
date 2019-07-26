#ifndef INFERNO_CORE_RENDERER_H_
#define INFERNO_CORE_RENDERER_H_

#include "../common.hpp"

class DisplayInterface;

class ProgressiveRenderer;

// Function initProgressive or whatever takes a pointer to the display
class Renderer {
public:
    Renderer(OperationMode mode);

    void SetMode(OperationMode mode, int samples = -1);

    void Init();

    void Init(DisplayInterface* display);

    void Render();
    void Render(uint32_t* framebuffer);

private:
    int m_samples = -1;
    OperationMode m_mode = MODE_DEFAULT;

    DisplayInterface* m_interface = nullptr;
    uint32_t* m_framebuffer = nullptr;

    void RenderProgressive();
    ProgressiveRenderer* m_progressive = nullptr;
    
    
    void RenderSamples();
};

#endif

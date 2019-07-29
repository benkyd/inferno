#ifndef INFERNO_CORE_RENDERER_H_
#define INFERNO_CORE_RENDERER_H_

#include "../common.hpp"

class DisplayInterface;

class ProgressiveRenderer;

class Scene;

// Function initProgressive or whatever takes a pointer to the display
class Renderer {
public:
    Renderer(OperationMode mode);

    void SetMode(OperationMode mode, int samples = -1);

    void Init();

    void Init(DisplayInterface* display);
    void InitRender(Scene* scene);

    bool RendererInitialized = false;

    void Render();
    void Render(uint32_t* framebuffer);

private:
    int m_samples = -1;
    OperationMode m_mode = MODE_DEFAULT;

    DisplayInterface* m_interface = nullptr;
    uint32_t* m_framebuffer = nullptr;

    Scene* m_scene = nullptr;

    void RenderProgressive();
    ProgressiveRenderer* m_progressive = nullptr;
    
    void RenderSamples();
    int m_sampleCount = -1;
};

#endif

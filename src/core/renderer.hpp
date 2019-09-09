#ifndef INFERNO_CORE_RENDERER_H_
#define INFERNO_CORE_RENDERER_H_

#include "../common.hpp"

class ProgressiveRenderer;
class DisplayInterface;
class FrameBuffer;

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
    void Render(FrameBuffer* framebuffer);

private:
    int m_samples = -1;
    OperationMode m_mode = MODE_OPERATION_PROGRESSIVE_GUI;

    DisplayInterface* m_interface = nullptr;
    FrameBuffer* m_framebuffer = nullptr;

    Scene* m_scene = nullptr;

    void RenderProgressive();
    ProgressiveRenderer* m_progressive = nullptr;
    
    void RenderSamples();
    int m_sampleCount = -1;
};

#endif

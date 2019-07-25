#ifndef INFERNO_CORE_RENDERER_H_
#define INFERNO_CORE_RENDERER_H_

#include "../common.hpp"

class Display;

// Function initProgressive or whatever takes a pointer to the display
class Renderer {
public:
    Renderer(OperationMode mode);

    void SetMode(OperationMode mode, int samples = -1);

    void Init();
    void Init(Display* display);

    void Render();

private:
    int m_samples = -1;
    OperationMode m_mode = MODE_DEFAULT;

    Display* m_display = nullptr;

    void RenderProgressive();
    void RenderSamples();

};

#endif

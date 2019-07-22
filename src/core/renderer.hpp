#ifndef INFERNO_CORE_RENDERER_H_
#define INFERNO_CORE_RENDERER_H_

#include "../common.hpp"

// Function initProgressive or whatever takes a pointer to the display
class Renderer {
public:
    Renderer(OperationMode mode);

    void Render();

private:
    OperationMode m_mode = MODE_DEFAULT;
};

#endif

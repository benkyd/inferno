#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

class DisplayInterface;

class ProgressiveRenderer {
public:
    ProgressiveRenderer();

    void Init(DisplayInterface* interface);

    void Render();

private:
    DisplayInterface* m_interface = nullptr; 
};

#endif

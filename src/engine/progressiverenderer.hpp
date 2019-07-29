#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

class DisplayInterface;

class Scene;

class ProgressiveRenderer {
public:
    ProgressiveRenderer();

    void Init(DisplayInterface* interface, Scene* scene);

    void Render();

private:
    DisplayInterface* m_interface = nullptr;

    Scene* m_scene = nullptr;
};

#endif

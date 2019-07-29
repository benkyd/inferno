#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

class DisplayInterface;

class Camera;
class Scene;

class ProgressiveRenderer {
public:
    ProgressiveRenderer();

    void Init(DisplayInterface* interface, Camera* camera, Scene* scene);

    void Render();

private:
    DisplayInterface* m_interface = nullptr;

    Camera* m_camera = nullptr;
    Scene* m_scene = nullptr;
};

#endif

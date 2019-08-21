#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

class DisplayInterface;
class Scene;

class ProgressiveRenderer {
public:
    ProgressiveRenderer();

    void Init(DisplayInterface* interface, Scene* scene);

	void Input();
    void Render();
	void RenderProgressive();

private:
    DisplayInterface* m_interface = nullptr;

    Scene* m_scene = nullptr;

	int m_workerMax = 16;
	std::vector<std::thread*> m_workers;

	bool m_mxaa = true;
};

#endif

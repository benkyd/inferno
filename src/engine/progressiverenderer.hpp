#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

#include "../common.hpp"
#include "../maths.hpp"

#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

class RenderThreadPool;
class DisplayInterface;
class RenderEngine;
class Scene;
class Ray;

class ProgressiveRenderer {
public:
    ProgressiveRenderer();

    void Init(DisplayInterface* interface, Scene* scene);

	void Input();
    void Render();
	void RenderProgressive();

	bool Ready = false;

public:
	RenderThreadPool* m_threadPool = nullptr;
    DisplayInterface* m_interface = nullptr;
	RenderEngine* m_engine = nullptr;
    Scene* m_scene = nullptr;

private:
	std::mutex m_mutex;

	bool m_normals = true;
};

#endif

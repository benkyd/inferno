#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

#include "../maths.hpp"

#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

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

	bool MXAA = true;
public:
    Scene* m_scene = nullptr;
    DisplayInterface* m_interface = nullptr;
	RenderEngine* m_engine = nullptr;

	int m_workerMax = 6;
	std::vector<std::thread*> m_workers;
	std::vector<bool> m_workerStatus;
private:
	std::mutex m_mutex;

	char* buf = ""; float f = 0.0f;
};

void workerThread(ProgressiveRenderer* renderer, int idd, int yStart, int yRange);

#endif

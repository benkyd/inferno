#ifndef INFERNO_ENGINE_PROGRESSIVERENDERER_H_
#define INFERNO_ENGINE_PROGRESSIVERENDERER_H_

#include "../common.hpp"
#include "../maths.hpp"

#include <vector>
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

	bool Ready = false;
	std::vector<float> FrameTimes = { };
	std::vector<float> AllFrameTimes = { };
	float AverageFrameTime = 0.0f;

public:
	RenderThreadPool* m_threadPool = nullptr;
    DisplayInterface* m_interface = nullptr;
	RenderEngine* m_engine = nullptr;
    Scene* m_scene = nullptr;

private:
	std::mutex m_mutex;

	void m_calculateTimes(std::chrono::high_resolution_clock::time_point frameStartTime,
						  std::chrono::high_resolution_clock::time_point frameEndTime);
	
	int m_renderModeSelected = 0;
	int m_toneMapModeSelected = 1;

	int m_framesRendererd = 0;
};

#endif

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
class Denoiser;
class Scene;
class Ray;

class ProgressiveRenderer {
public:
	// Default constructor (unused)
    ProgressiveRenderer();

	// Initializes the renderer, takes the display interface
	// that it will be rendering too, this manages windows and
	// that and based on that it will decide if it is going 
	// to use imgui or not, and based on user preferance
    void Init(DisplayInterface* interface, Scene* scene);

	// Takes program input and updates imgui if it is active
	// can manipulate scene based on input but im going to 
	// give a way for the end user to do that as well as a
	// much broader imgui interface
	void Input();

	// Starts the rendering process. This function does not return
	// until program end / window close and it calls input every frame
    void Render();

	// Indicates to the threadpool if the progressive renderer is ready
	// and will tell them to start the render
	bool Ready = false;
	
	// Last 10 frame times to calculate average from
	std::vector<float> FrameTimes = { };
	// All frame times since program start
	std::vector<float> AllFrameTimes = { };
	// Average time of the last 10 frames for a more accurate fps
	float AverageFrameTime = 0.0f;

	// If MXAA is enabled
	bool MXAA = true;

public:
	// Pointers to 
	RenderThreadPool* m_threadPool = nullptr;
    DisplayInterface* m_interface = nullptr;
	RenderEngine* m_engine = nullptr;
	Denoiser* m_denoiser = nullptr;
    Scene* m_scene = nullptr;

private:
	std::mutex m_mutex;

	// Calculates the frametime and updates the frametime clocks
	void m_calculateTimes(std::chrono::high_resolution_clock::time_point& frameStartTime,
						  std::chrono::high_resolution_clock::time_point& frameEndTime);
	
	// ints that map directly to RenderMode and ToneMapMode
	// and are used to set them, must be indexed correctly
	// according to the enums
	int m_renderModeSelected = 0;
	int m_toneMapModeSelected = 0;


	int m_framesRendererd = 0;

	// Gamma to pass to the framebuffer
	float m_gamma = 2.3f;

	// Image save path to pass to the framebuffer
	std::string m_imageSavePath = "image.png";

	RenderMode m_mode = (RenderMode)m_renderModeSelected;
};

#endif

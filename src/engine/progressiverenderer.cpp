#include "progressiverenderer.hpp"

#include <numeric>
#include <sstream>
#include <chrono>

#include "renderengine.hpp"

#include "../common.hpp"
#include "../pixel.hpp"

#include "../display/displayinterface.hpp"
#include "../display/framebuffer.hpp"

#include "../util/assetloader.hpp"
#include "../util/threadpool.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

ProgressiveRenderer::ProgressiveRenderer() {
    
}

void ProgressiveRenderer::Init(DisplayInterface* interface, Scene* scene) {
	m_threadPool = new RenderThreadPool();
	m_engine = new RenderEngine();
	m_engine->Mode = MODE_RENDER_PATHTRACE;
	m_engine->SetScene(scene);
    m_interface = interface;
	m_scene = scene;
}

void ProgressiveRenderer::Input() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT) m_interface->Close();
	
	const Uint8* state = SDL_GetKeyboardState(NULL);

	//glm::vec3 pos = m_scene->objects[0]->center;
	//if (state[SDL_SCANCODE_W]) m_scene->objects[0]->center.y += 0.01f;
	//if (state[SDL_SCANCODE_S]) m_scene->objects[0]->center.y -= 0.01f;
	//if (state[SDL_SCANCODE_D]) m_scene->objects[0]->center.x += 0.01f;
	//if (state[SDL_SCANCODE_A]) m_scene->objects[0]->center.x -= 0.01f;
	//if (state[SDL_SCANCODE_R]) m_scene->objects[0]->center.z += 0.01f;
	//if (state[SDL_SCANCODE_F]) m_scene->objects[0]->center.z -= 0.01f;
	//glm::vec3 newpos = m_scene->objects[0]->center;
	
	//if (newpos.x != pos.x || newpos.y != pos.y || newpos.z != pos.z) {
	//	m_threadPool->ThreadFrameBuffer->ClearFramebuffer();
	//	m_engine->SPP = 0; m_engine->SPPDepth = 0;
	//}

	if (!m_interface->ImGui) return;

	ImGui::NewFrame();
	ImGui::Begin("Debug");

	if (m_engine->Mode == MODE_RENDER_PATHTRACE) {
		std::stringstream str; str << "SPP: " << m_engine->SPP;
		ImGui::Text(str.str().c_str());
	} else if (m_engine->Mode == MODE_RENDER_PATH_BOUNCES) {
		std::stringstream str; str << "Depth SPP: " << m_engine->SPPDepth;
		ImGui::Text(str.str().c_str());
	}
	std::stringstream str0; str0 << "FPS: " << 1.0f / AverageFrameTime;
	ImGui::Text(str0.str().c_str());
	std::stringstream str1; str1 << "MS Per Frame: " << AverageFrameTime * 1000.0f;
	ImGui::Text(str1.str().c_str());
	std::stringstream str2; str2 << "S Per Frame:  " << AverageFrameTime;
	ImGui::Text(str2.str().c_str());

	float upper = 0.0f; float lower = 0.0f;
	for (int i = 0; i < AllFrameTimes.size(); i++) {
		if (AllFrameTimes[i] > upper) upper = AllFrameTimes[i];
		if (AllFrameTimes[i] < lower) lower = AllFrameTimes[i];
	}
	ImGui::PlotLines("FrameTimes", FrameTimes.data(), FrameTimes.size(), 0, NULL, lower, upper, ImVec2(0, 40));
	
	const char* renderItems[] = { "PathTrace", "Normals", "Path Bounces", "Path Length" };
	ImGui::Combo("Render Mode", &m_renderModeSelected, renderItems, IM_ARRAYSIZE(renderItems));
	m_mode = (RenderMode)m_renderModeSelected;

	const char* toneMapItems[] = { "Reinhard Tonamap", "Exponential Tonemap", "Clamp", "Basic Tonemap" };
	ImGui::Combo("ToneMap Mode", &m_toneMapModeSelected, toneMapItems, IM_ARRAYSIZE(toneMapItems));

	ImGui::SliderFloat("Gamma", &m_gamma, 1.0f, 4.0f);
	m_interface->Framebuffer->Gamma = 1.0f / m_gamma;

	if (ImGui::Button("Reset")) {
		m_threadPool->ThreadFrameBuffer->ClearFramebuffer();
		m_engine->SPP = 0; m_engine->SPPDepth = 0;
	}

	if (ImGui::Button("Save Image")) {
		m_interface->Framebuffer->DumpToFile(m_imageSavePath);
		std::cout << "Saved: " << m_imageSavePath << std::endl;
	}
	
	ImGui::End();
}

void ProgressiveRenderer::Render() {
	m_threadPool->SetJobs(this, m_scene->w, m_scene->h);
	m_engine->Mode = m_mode;

	std::chrono::high_resolution_clock::time_point frameStartTime = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point frameEndTime;

	Ready = true;
	m_threadPool->Ready = true;
	while (m_interface->Active) {		
		if (m_threadPool->CheckAllJobs()) {
			m_engine->Mode = m_mode;
			m_engine->PostProcess(m_threadPool->ThreadFrameBuffer->RenderTarget, m_threadPool->ThreadFrameBuffer->RenderPostProcess, m_scene->w, m_scene->h);

			// Denoise in HDR space

			m_threadPool->ThreadFrameBuffer->PostProcess((ToneMapMode)m_toneMapModeSelected);

			m_threadPool->MergeBuffers(m_interface->Framebuffer);
			m_interface->Framebuffer->Ready();

			m_threadPool->RunJobsAgain();

			m_calculateTimes(frameStartTime, frameEndTime);
		}

		Input();
		m_interface->Update();
	}

	Ready = false;
	m_threadPool->Destroy();
}


void ProgressiveRenderer::m_calculateTimes(std::chrono::high_resolution_clock::time_point& frameStartTime,
										   std::chrono::high_resolution_clock::time_point& frameEndTime) {
	frameEndTime = std::chrono::high_resolution_clock::now();
	m_framesRendererd++;

	float frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime).count();
	frameTime /= 1000;

	FrameTimes.push_back(frameTime);
	AllFrameTimes.push_back(frameTime);
	if (FrameTimes.size() > 11) FrameTimes.erase(FrameTimes.begin());

	AverageFrameTime = std::accumulate(FrameTimes.begin(), FrameTimes.end(), 0.0) / FrameTimes.size();
	frameStartTime = std::chrono::high_resolution_clock::now();
}

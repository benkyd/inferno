#include "progressiverenderer.hpp"

#include <numeric>
#include <sstream>
#include <chrono>

#include "renderengine.hpp"

#include "../common.hpp"
#include "../pixel.hpp"


#include "../display/displayinterface.hpp"
#include "../display/framebuffer.hpp"
#include "../display/tonemapfb.hpp"

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

	//if (state[SDL_SCANCODE_W]) m_scene->objects[0]->center.y += 0.01f;
	//if (state[SDL_SCANCODE_S]) m_scene->objects[0]->center.y -= 0.01f;
	//if (state[SDL_SCANCODE_D]) m_scene->objects[0]->center.x += 0.01f;
	//if (state[SDL_SCANCODE_A]) m_scene->objects[0]->center.x -= 0.01f;

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

	const char* toneMapItems[] = { "Clamp", "Basic Tonemap" };
	ImGui::Combo("ToneMap Mode", &m_toneMapModeSelected, toneMapItems, IM_ARRAYSIZE(toneMapItems));

	ImGui::SliderFloat("Gamma", &m_gamma, 1.0f, 3.0f);
	m_interface->Framebuffer->Gamma = 1.0f / m_gamma;

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
			m_engine->PostProcess(m_threadPool->MappedThreadFrameBuffer->RenderTo, m_threadPool->MappedThreadFrameBuffer->ProcData, m_scene->w, m_scene->h);

			if (m_engine->Mode != MODE_RENDER_NORMALS) {
				if (m_toneMapModeSelected == 0) m_threadPool->MappedThreadFrameBuffer->ClampBasic(m_threadPool->ThreadFrameBuffer);
			
				if (m_toneMapModeSelected == 1) m_threadPool->MappedThreadFrameBuffer->MapBasic(m_threadPool->ThreadFrameBuffer);
			} else {
				m_threadPool->MappedThreadFrameBuffer->ClampBasic(m_threadPool->ThreadFrameBuffer);
			}

			m_threadPool->MergeBuffers(m_interface->Framebuffer->Data, m_scene->w, m_scene->h);
			m_threadPool->RunJobsAgain();

			frameEndTime = std::chrono::high_resolution_clock::now();
			m_calculateTimes(frameStartTime, frameEndTime);
			frameStartTime = std::chrono::high_resolution_clock::now();
		}

		Input();
		m_interface->Update();
	}

	Ready = false;
	m_threadPool->Destroy();
}


void ProgressiveRenderer::m_calculateTimes(std::chrono::high_resolution_clock::time_point frameStartTime,
										   std::chrono::high_resolution_clock::time_point frameEndTime) {
	m_framesRendererd++;

	float frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime).count();
	frameTime /= 1000;

	FrameTimes.push_back(frameTime);
	AllFrameTimes.push_back(frameTime);
	if (FrameTimes.size() > 11) FrameTimes.erase(FrameTimes.begin());

	AverageFrameTime = std::accumulate(AllFrameTimes.begin(), AllFrameTimes.end(), 0.0) / AllFrameTimes.size();
}

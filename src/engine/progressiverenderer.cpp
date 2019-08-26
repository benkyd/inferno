#include "progressiverenderer.hpp"

#include "renderengine.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

#include "../util/assetloader.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

ProgressiveRenderer::ProgressiveRenderer() {
    
}

void ProgressiveRenderer::Init(DisplayInterface* interface, Scene* scene) {
	m_engine = new RenderEngine();
	m_engine->SetScene(scene);
    m_interface = interface;
	m_scene = scene;
}

void ProgressiveRenderer::Input() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT) m_interface->Close();
	
	if (!m_interface->ImGui) return;

	ImGui::NewFrame();
	ImGui::Begin("Debug");
	ImGui::End();
}

void workerThread(ProgressiveRenderer* renderer, int idd, int yStart, int yRange) {
	while (!renderer->Ready) { 
		std::chrono::milliseconds dura(10);
		std::this_thread::sleep_for(dura);
	}

	while (renderer->Ready) {
		for (int y = yStart; y < yStart + yRange; y++)
		for (int x = 0; x < renderer->m_scene->w; x++) {
			Ray ray = renderer->m_scene->camera->CastRay(x, y);
			glm::vec3 col = renderer->m_engine->GetColour(ray, 0);
			renderer->m_interface->SetPixelSafe(x, y, col);
		}
	}
}

void ProgressiveRenderer::Render() {

	/* 
		New design is needed
		as follows is pretty
		good

		class threadpool {
			vector thread* threads
			vector bool status
			vector uint32 buffers
			void merge()
		}
	
		maybe

		class thread {
			framebuffer
		}
	*/

	// Allocates threads with ranges to render
	for (int i = 0; i < m_workerMax; i++) {
		if (i == m_workerMax - 1) {
			m_workers.push_back(new std::thread(workerThread, this, i, 
				(m_scene->h / m_workerMax) * i, 
				-((m_scene->h / m_workerMax) * i - m_scene->h)
			));
		} else {
			m_workers.push_back(new std::thread(workerThread, this, i,
				(m_scene->h / m_workerMax) * i, 
				(m_scene->h / m_workerMax) * (i + 1) - (m_scene->h / m_workerMax) * i
			));
		}
	}

	int lastTime = SDL_GetTicks();
	// Starts render loop
	while (m_interface->Active) {
		Ready = true;
		
		// TODO: Queue frame jobs properly
		
		Input();
		m_interface->Update();
	}

	Ready = false;
	for (auto& thread : m_workers) {
		thread->join();
	}
}

void ProgressiveRenderer::RenderProgressive() {

}

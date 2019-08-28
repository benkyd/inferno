#include "progressiverenderer.hpp"

#include "renderengine.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

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
	
	if (!m_interface->ImGui) return;

	ImGui::NewFrame();
	ImGui::Begin("Debug");
	ImGui::Checkbox("Render Normals", &m_normals);
	if (m_normals) {
		m_engine->Mode = MODE_RENDER_NORMALS;
	} else {
		m_engine->Mode = MODE_RENDER_PATHTRACE;
	}
	ImGui::End();
}

void ProgressiveRenderer::Render() {
	m_threadPool->SetJobs(this, m_scene->w, m_scene->h);

	// Starts render loop
	Ready = true;
	m_threadPool->Ready = true;
	while (m_interface->Active) {		
		if (m_threadPool->CheckAllJobs()) m_threadPool->RunJobsAgain();

		Input();
		m_interface->Update();
	}

	Ready = false;
	m_threadPool->Destroy();
}

void ProgressiveRenderer::RenderProgressive() {

}

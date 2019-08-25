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
	ImGui::Text("Hello, world %d", 123);
	if (ImGui::Button("Save")) {}
	ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::End();
}

void workerThread(ProgressiveRenderer* renderer, int idd, int xStart, int xRange) {
	while (!renderer->Ready) { 
		std::chrono::milliseconds dura(10);
		std::this_thread::sleep_for(dura);
	}

	while (renderer->Ready) {
		for (int x = xStart; x < xStart + xRange; x++)
		for (int y = 0; y < renderer->m_scene->h; y++) {
			Ray ray = renderer->m_scene->camera->CastRay(x, y);
			glm::vec3 col = renderer->m_engine->GetColour(ray, 0);
			renderer->m_interface->SetPixelSafe(x, y, col);
		}
	}
}

void ProgressiveRenderer::Render() {
    int frames = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

	// Allocates threads with ranges to render
	for (int i = 0; i < m_workerMax; i++) {
		if (i == m_workerMax - 1) {
			m_workers.push_back(new std::thread(workerThread, this, i, 
				(m_scene->w / m_workerMax) * i, 
				-((m_scene->w / m_workerMax) * i - m_scene->w)
			));
		} else {
			m_workers.push_back(new std::thread(workerThread, this, i,
				(m_scene->w / m_workerMax) * i, 
				(m_scene->w / m_workerMax) * (i + 1) - (m_scene->w / m_workerMax) * i
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

    // auto frameStartTime = std::chrono::high_resolution_clock::now();

    // auto endTime = std::chrono::high_resolution_clock::now();

    // frames++;
    // std::cout << "Frame: " << frames << std::endl;
    // std::cout << "Frame Time:     " << std::chrono::duration_cast<std::chrono::seconds>(endTime - frameStartTime).count()
    //           << ":" << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - frameStartTime).count() << "s" << std::endl;
    // std::cout << "Avg Frame Time: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() / frames
    //           << ":" << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / frames << "s"
    //           << std::endl << std::endl;

    // Swap framebuffers
    // m_interface->Update();
	// m_interface->ClearFramebuffer();
}

void ProgressiveRenderer::RenderProgressive() {

}

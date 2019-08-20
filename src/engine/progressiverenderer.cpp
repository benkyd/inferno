#include "progressiverenderer.hpp"

#include <vector>
#include <chrono>

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
    m_interface = interface;
    m_scene = scene;
}

void ProgressiveRenderer::Render() {
    int frames = 0;
    auto startTime = std::chrono::high_resolution_clock::now();


    while (m_interface->Active) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();

		ImGui::NewFrame();
		ImGui::Begin("Thing");
		ImGui::Text("Hello, world %d", 123);
		if (ImGui::Button("Save")) {}
		char* buf = ""; float f;
		ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::End();

		#pragma omp parallel for schedule(dynamic)
        for (int x = 0; x < m_scene->w; x++)
        for (int y = 0; y < m_scene->h; y++) {

            SDL_Event e;
            while (SDL_PollEvent(&e)) 
                if (e.type == SDL_QUIT) m_interface->Close();

            Ray ray = m_scene->camera->CastRay(x, y);

            float t;
            Primative* hit = nullptr;
			bool didhit = TraceRayScene(ray, m_scene, t, hit);
            if (!didhit) {
                m_interface->SetPixelSafe(x, y, 0x000000);
                continue;
            }
    
            glm::vec3 hitPoint = ray.origin + ray.direction * t;

            glm::vec3 normal = hit->SurfaceNormal(hitPoint);
            Pixel col((normal.x + 1.0f) * 127.5f, (normal.y + 1.0f) * 127.5f, (normal.z + 1.0f) * 127.5f);
            m_interface->SetPixelSafe(x, y, col.rgb());
        }


        auto endTime = std::chrono::high_resolution_clock::now();

        frames++;
        std::cout << "Frame: " << frames << std::endl;
        std::cout << "Frame Time:     " << std::chrono::duration_cast<std::chrono::seconds>(endTime - frameStartTime).count()
                  << ":" << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - frameStartTime).count() << std::endl;
        std::cout << "Avg Frame Time: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() / frames
                  << ":" << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / frames 
                  << std::endl << std::endl;

        // Swap framebuffers
        m_interface->Update();
    }
}

#include "progressiverenderer.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

#include "../util/assetloader.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/primatives/triangle.hpp"
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
    m_scene->objects = LoadTrianglesBasic("/home/ben/programming/inferno/resources/cornell.obj");
    for (const auto& object : m_scene->objects)
		object->Translate({ 0.0f, -1.0f, -3.0f });

    while (m_interface->Active) {

        // Take input
        SDL_Event e;
        while (SDL_PollEvent(&e)) 
            if (e.type == SDL_QUIT) m_interface->Close();

		#pragma omp parallel for schedule(dynamic)
        for (int x = 0; x < m_scene->w; x++)
        for (int y = 0; y < m_scene->h; y++) {
            Ray ray = m_scene->camera->CastRay(x, y);
            
            float t, i;
            bool didhit = TraceRay(ray, m_scene, t, i);
            if (!didhit) {
                m_interface->SetPixelSafe(x, y, 0x000000);
                continue;
            }
    
            Primative* hit = m_scene->objects[i];
            glm::vec3 hitPoint = ray.origin + ray.direction * t;


            glm::vec3 normal = hit->SurfaceNormal(hitPoint);
            Pixel col((normal.x + 1.0f) * 127.5f, (normal.y + 1.0f) * 127.5f, (normal.z + 1.0f) * 127.5f);
            m_interface->SetPixelSafe(x, y, col.rgb());
        }

        // Swap framebuffers
        m_interface->Update();
    }
}

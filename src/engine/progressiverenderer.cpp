#include "progressiverenderer.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

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
    while (m_interface->Active) {

        // Take input
        SDL_Event e;
        while (SDL_PollEvent(&e)) 
            if (e.type == SDL_QUIT) m_interface->Close();

		#pragma omp parallel for schedule(dynamic)
        for (int x = 0; x < m_scene->w; x++)
        for (int y = 0; y < m_scene->h; y++) {
            Ray ray = m_scene->camera->CastRay(x, y);
            
            for (int i = 0; i < m_scene->objects.size(); i++) {
                Primative* smh = m_scene->objects[i];
                float t = 0;
                if (smh->DoesIntersect(ray, t)) {
                    if (smh->type == TYPE_SPHERE) {
                        m_interface->SetPixelSafe(x, y, 0x00FF00);
                    } else if (smh->type == TYPE_PLANE) {
                        m_interface->SetPixelSafe(x, y, 0x00FFFF);
                    } else {
                        m_interface->SetPixelSafe(x, y, 0xFF00FF);
                    }
                }
            }
        }

        m_scene->objects[1]->center.y += 0.01f;

        // Swap framebuffers
        m_interface->Update();
    }
}

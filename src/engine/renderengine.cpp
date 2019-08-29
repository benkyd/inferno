#include "renderengine.hpp"

#include "../pixel.hpp"
#include "../util/threadpool.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

#include "../display/displayinterface.hpp"
#include "../display/framebuffer.hpp"
#include "../display/tonemap.hpp"

#include "../engine/renderengine.hpp"
#include "../engine/progressiverenderer.hpp"

void workerThread(RenderThreadPool* threadpool, ProgressiveRenderer* renderer, int idd, int yStart, int yRange) {
	while (!renderer->Ready && !threadpool->Ready) {
		std::chrono::milliseconds dura(10);
		std::this_thread::sleep_for(dura);
	}

	while (renderer->Ready && threadpool->Ready) {

		for (int y = yStart; y < yStart + yRange; y++)
		for (int x = 0; x < renderer->m_scene->w; x++) {
			Ray ray = renderer->m_scene->camera->CastRay(x, y);
			glm::vec3 col = renderer->m_engine->GetColour(ray, 0);
			threadpool->MappedThreadFrameBuffer->SetPixelSafe(x, y, col);
		}
		
		threadpool->ThreadStatus[idd] = true;

		while (threadpool->ThreadStatus[idd]) { }
	}
}

RenderEngine::RenderEngine() {

}

void RenderEngine::SetScene(Scene* scene) {
	m_scene = scene;
}

glm::vec3 RenderEngine::GetColour(Ray ray, int depth) {

	float t; Primative* hit = nullptr;
	bool didhit = TraceRayScene(ray, m_scene, t, hit);
	if (!didhit) {
		return 	m_scene->SampleSky(ray);
	}

	glm::vec3 hitPoint = ray.origin + ray.direction * t;

	if (Mode == MODE_RENDER_NORMALS) return GetNormalColour(hit, hitPoint);

	return { 1.0f, 1.0f, 1.0f };
}

glm::vec3 RenderEngine::GetNormalColour(Primative* hit, glm::vec3 hitPoint) {
	glm::vec3 normal = hit->SurfaceNormal(hitPoint);
	return { ((normal.x + 1.0f) * 127.5f) / 255.0f, ((normal.y + 1.0f) * 127.5f) / 255.0f, ((normal.z + 1.0f) * 127.5f) / 255.0f };
}

#include "renderengine.hpp"

#include "../pixel.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

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

	glm::vec3 normal = hit->SurfaceNormal(hitPoint);

	return { (normal.x + 1.0f) * 127.5f, (normal.y + 1.0f) * 127.5f, (normal.z + 1.0f) * 127.5f };
}

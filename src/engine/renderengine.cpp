#include "renderengine.hpp"

#include <random>

#include "../pixel.hpp"
#include "../util/threadpool.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

#include "../display/displayinterface.hpp"
#include "../display/framebuffer.hpp"
#include "../display/tonemapfb.hpp"

#include "../engine/renderengine.hpp"
#include "../engine/progressiverenderer.hpp"

static glm::vec3 Black{ 0.0f, 0.0f, 0.0f };
static glm::vec3 White{ 1.0f, 1.0f, 1.0f };
static glm::vec3 Red  { 1.0f, 0.2f, 0.2f };
static glm::vec3 Green{ 0.2f, 1.0f, 0.2f };
static glm::vec3 Blue { 0.2f, 0.2f, 1.0f };

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
			
			if (renderer->m_engine->Mode == MODE_RENDER_NORMALS) {
				threadpool->MappedThreadFrameBuffer->SetPixelSafe(x, y, col);
			} else {
				// threadpool->MappedThreadFrameBuffer->SetPixelSafe(x, y, col);
				threadpool->MappedThreadFrameBuffer->AddPixelSafe(x, y, col);
			}
		}
		
		threadpool->ThreadStatus[idd] = true;

		while (threadpool->ThreadStatus[idd]) {
			std::chrono::nanoseconds dura(1);
			std::this_thread::sleep_for(dura);
		}
	}
}

RenderEngine::RenderEngine() {

}

void RenderEngine::SetScene(Scene* scene) {
	m_scene = scene;
}

std::default_random_engine generator;
// std::uniform_real_distribution<float> distribution(-1,1);
// (float)rand() / float(RAND_MAX)*2.0f - 1.0f;

float rand01() {
	std::uniform_real_distribution<float> distribution(0, 1);
	return distribution(generator);
}

glm::vec3 CosineBRDF(glm::vec3 normal) {
	const float TWO_PI = 2.0f * PI;

	float r0 = rand01();
	float r1 = rand01();

	glm::vec3 uu = glm::normalize(glm::cross(normal, { 0.0f, 1.0f, 1.0f }));
	glm::vec3 vv = glm::cross(uu, normal);

	float ra = sqrtf(r1);

	float rx = ra * cosf(TWO_PI * r0);
	float ry = ra * sinf(TWO_PI * r0);

	float rz = sqrtf(1.0f - r1);

	return glm::normalize(rx * uu + ry * vv + rz * normal);
}

glm::vec3 RenderEngine::GetColour(Ray ray, int depth) {
	if (depth > 6) return { 0.0f, 0.0f, 0.0f };

	float t; Primative* hit = nullptr;
	bool didhit = TraceRayScene(ray, m_scene, t, hit);
	if (!didhit) return	m_scene->SampleSky(ray);

	glm::vec3 hitPoint = ray.origin + ray.direction * t;
	glm::vec3 normal = hit->SurfaceNormal(hitPoint);
	if (Mode == MODE_RENDER_NORMALS) { return GetNormalColour(normal); }

	std::uniform_real_distribution<float> distribution(0, 2);
	int col = round(distribution(generator));

	glm::vec3 colour = { 1.0f, 1.0f, 1.0f };
	if (hit->type == TYPE_PLANE) {
		glm::vec2 uv = hit->TexCoords(hitPoint);
		float angle = fastDegreetoRadian(.0f);
		float s = uv.x * cos(angle) - uv.y * sin(angle);
		float t = uv.y * cos(angle) + uv.x * sin(angle);
		float S = 0.05f; float T = 0.05f;
		float pattern = (modulo(s * S) < 0.5f) ^ (modulo(t * T) < 0.5f);
		colour.r = pattern; colour.g = pattern; colour.b = pattern;
	}

	glm::vec3 direction = CosineBRDF(normal);

	Ray newRay{ hitPoint, direction };

	// Prevent acne
	if (glm::dot(newRay.direction, normal) < 0.0f) {
		newRay.origin = ray.origin + ray.direction * t - normal * EPSILON;
	}
	else {
		newRay.origin = ray.origin + ray.direction * t + normal * EPSILON;
	}

	return GetColour(newRay, depth + 1) * colour;
}

void RenderEngine::PostProcess(glm::vec3* src, glm::vec3* dst, int w, int h) {
	if (Mode == MODE_RENDER_NORMALS) { 
		for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			dst[y * w + x] = src[y * w + x];
		}	
		SPP = 0;
		return; 
	}

	SPP++;
	for (int y = 0; y < h; y++)
	for (int x = 0; x < w; x++) {
		dst[y * w + x] = src[y * w + x] / (float)SPP;
	}
}

glm::vec3 RenderEngine::GetNormalColour(glm::vec3 normal) {
	return ((normal + 1.0f) * 127.5f) / 255.0f;
}

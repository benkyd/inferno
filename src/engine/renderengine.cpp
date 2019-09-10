#include "renderengine.hpp"

#include "../pixel.hpp"
#include "../util/threadpool.hpp"

#include "../definitions/materials/material.hpp"
#include "../definitions/materials/random.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

#include "../display/displayinterface.hpp"
#include "../display/framebuffer.hpp"

#include "../engine/renderengine.hpp"
#include "../engine/progressiverenderer.hpp"

static glm::vec3 Black{ 0.0f, 0.0f, 0.0f };
static glm::vec3 White{ 1.0f, 1.0f, 1.0f };
static glm::vec3 Red  { 1.0f, 0.2f, 0.2f };
static glm::vec3 Green{ 0.2f, 1.0f, 0.2f };
static glm::vec3 Blue { 0.2f, 0.2f, 1.0f };

void workerThread(RenderThreadPool* threadpool, ProgressiveRenderer* renderer, int idd, int yStart, int yRange) {
	while (!renderer->Ready && !threadpool->Ready) {
		static std::chrono::milliseconds dura(10);
		std::this_thread::sleep_for(dura);
	}

	while (renderer->Ready && threadpool->Ready) {

		for (int y = yStart; y < yStart + yRange; y++)
		for (int x = 0; x < renderer->m_scene->w; x++) {
			
			Ray ray = {};
			
			if (renderer->MXAA) 
				ray = renderer->m_scene->camera->CastRay(x, y, rand01(), rand01());
			else
				ray = renderer->m_scene->camera->CastRay(x, y);

			int depth = 0;
			glm::vec3 col = renderer->m_engine->GetColour(ray, depth);
			
			if (renderer->m_engine->Mode == MODE_RENDER_NORMALS || renderer->m_engine->Mode == MODE_RENDER_PATH_LENGTH) {
				threadpool->ThreadFrameBuffer->SetPixelSafe(x, y, col);
			} else if (renderer->m_engine->Mode == MODE_RENDER_PATH_BOUNCES) {
				col.r = depth; col.g = depth / 3.0f; col.b = depth / 3.0f;
				threadpool->ThreadFrameBuffer->AddPixelSafe(x, y, col, (int)renderer->m_engine->Mode);
			} else {
				threadpool->ThreadFrameBuffer->AddPixelSafe(x, y, col, (int)renderer->m_engine->Mode);
			}
		}
		
		threadpool->ThreadStatus[idd] = true;

		while (threadpool->ThreadStatus[idd]) {
			static std::chrono::nanoseconds dura(1);
			std::this_thread::sleep_for(dura);
		}
	}
}

RenderEngine::RenderEngine() {

}

void RenderEngine::SetScene(Scene* scene) {
	m_scene = scene;
}

glm::vec3 RenderEngine::GetColour(Ray ray, int& depth) {
	if (depth > 5) return { 0.0f, 0.0f, 0.0f };

	float t = INFINITY; Primative* hit = nullptr;
	bool didhit = TraceRayScene(ray, m_scene, t, hit);
	if (!didhit) return	m_scene->SampleSky(ray);

	glm::vec3 hitPoint = ray.origin + ray.direction * t;
	glm::vec3 normal = hit->SurfaceNormal(hitPoint);
	if (Mode == MODE_RENDER_NORMALS) { return GetNormalColour(normal); }
	if (Mode == MODE_RENDER_PATH_LENGTH) { if (t > 1000.0f) t = 1000.0f; return { (float)t, (float)t, (float)t }; }

	glm::vec3 colour = hit->material->Colour;
	//if (hit->type == TYPE_PLANE) {
	//	glm::vec2 uv = hit->TexCoords(hitPoint);
	//	float angle = fastDegreetoRadian(.0f);
	//	float s = uv.x * cos(angle) - uv.y * sin(angle);
	//	float t = uv.y * cos(angle) + uv.x * sin(angle);
	//	float S = 0.4f; float T = 0.4f;
	//	float pattern = (modulo(s * S) < 0.5f) ^ (modulo(t * T) < 0.5f);
	//	colour.r = pattern; colour.g = pattern; colour.b = pattern;
	//}


	if (hit->material->Emissive) return (colour * hit->material->Emittance);

	glm::vec3 direction = hit->material->Bounce(ray.direction, normal);

	Ray newRay{ hitPoint, direction };

	// Prevent acne
	if (glm::dot(newRay.direction, normal) < 0.0f) {
		newRay.origin = ray.origin + ray.direction * t - normal * EPSILON;
	} else {
		newRay.origin = ray.origin + ray.direction * t + normal * EPSILON;
	}

	depth++;
	return GetColour(newRay, depth) * colour;
}

void RenderEngine::PostProcess(glm::vec3* src, glm::vec3* dst, int w, int h) {
	if (Mode == MODE_RENDER_NORMALS || Mode == MODE_RENDER_PATH_LENGTH) { 
		SPP = 0;
		for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			dst[y * w + x] = src[y * w + x];
		}	
		return; 
	}

	if (Mode == MODE_RENDER_PATH_BOUNCES) {
		SPP = 0;
		SPPDepth++;
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++) {
				dst[y * w + x] = src[y * w + x] / (float)SPPDepth;
			}
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

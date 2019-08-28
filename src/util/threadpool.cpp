#include "threadpool.hpp"

#include "../definitions/ray.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/camera.hpp"

#include "../display/displayinterface.hpp"
#include "../display/framebuffer.hpp"

#include "../engine/renderengine.hpp"
#include "../engine/progressiverenderer.hpp"

RenderThreadPool::RenderThreadPool() {
	for (int i = 0; i < ThreadCount; i++) {
		ThreadStatus.push_back(false);
	}
};

void RenderThreadPool::SetJobs(ProgressiveRenderer* renderer, int x, int y) {
	for (int i = 0; i < ThreadCount; i++) {
		if (i == ThreadCount - 1) {
			Pool.push_back(new std::thread(workerThread, this, renderer, i,
				 (x / ThreadCount) * i,
			   -((x / ThreadCount) * i - x)
			));
		}
		else {
			Pool.push_back(new std::thread(workerThread, this, renderer, i,
				(y / ThreadCount) * i,
				(y / ThreadCount) * (i + 1) - (y / ThreadCount) * i
			));
		}
	}
}

void RenderThreadPool::BeginJobs() {
	Ready = true;
}

bool RenderThreadPool::CheckAllJobs() {
	bool ret = false;

	bool last = ThreadStatus[0];
	for (int i = 1; i < ThreadCount; i++) {
		if (ThreadStatus[i] != last) return false;
		ThreadStatus[i] = last;
	}

	return last;
}

void RenderThreadPool::RunJobsAgain() {
	ThreadLock.lock();
	for (int i = 0; i < ThreadCount; i++) {
		ThreadStatus[i] = false;
	}
	ThreadLock.unlock();
}

void RenderThreadPool::MergeBuffers(uint32_t* Framebuffer) {

}

void RenderThreadPool::Destroy() {

}

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
			renderer->m_interface->Framebuffer->SetPixelSafe(x, y, col);
		}

		threadpool->ThreadLock.lock();
		threadpool->ThreadStatus[idd] = true;
		threadpool->ThreadLock.unlock();

		while (threadpool->ThreadStatus[idd]) { 
			std::chrono::milliseconds dura(1);
			std::this_thread::sleep_for(dura);
		}
	}
}

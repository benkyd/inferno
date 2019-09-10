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

void RenderThreadPool::SetJobs(ProgressiveRenderer* renderer, int w, int h) {
	ThreadFrameBuffer = new FrameBuffer(w, h);
	for (int i = 0; i < ThreadCount; i++) {
		if (i == ThreadCount - 1) {
			Pool.push_back(new std::thread(workerThread, this, renderer, i,
				 (w / ThreadCount) * i,
			   -((w / ThreadCount) * i - w)
			));
			//RenderRegions.push_back({ ((w / ThreadCount) * i) * w, 
			//						(-((w / ThreadCount) * i  - w)) * w });
		} else {
			Pool.push_back(new std::thread(workerThread, this, renderer, i,
				(h / ThreadCount) * i,
				(h / ThreadCount) * (i + 1) - (h / ThreadCount) * i
			));
			//RenderRegions.push_back({ ((h / ThreadCount) * i) * w, 
			//						  ((h / ThreadCount) * (i + 1) - (h / ThreadCount) * i) * w });
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

void RenderThreadPool::MergeBuffers(FrameBuffer* framebuffer) {	
	memcpy((void*)framebuffer->RenderNormalsTarget, (void*)ThreadFrameBuffer->RenderNormalsTarget, (framebuffer->XRes * framebuffer->YRes) * sizeof(glm::vec3));
	memcpy((void*)framebuffer->RenderAlbedoTarget,  (void*)ThreadFrameBuffer->RenderAlbedoTarget,  (framebuffer->XRes * framebuffer->YRes) * sizeof(glm::vec3));
	memcpy((void*)framebuffer->RenderTarget,        (void*)ThreadFrameBuffer->RenderTarget, 	   (framebuffer->XRes * framebuffer->YRes) * sizeof(glm::vec3));
	memcpy((void*)framebuffer->RenderPostProcess,   (void*)ThreadFrameBuffer->RenderPostProcess,   (framebuffer->XRes * framebuffer->YRes) * sizeof(glm::vec3));
	memcpy((void*)framebuffer->RenderData,		    (void*)ThreadFrameBuffer->RenderData, 		   (framebuffer->XRes * framebuffer->YRes) * sizeof(uint32_t));
}

void RenderThreadPool::Destroy() {

}

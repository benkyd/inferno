#ifndef INFERNO_UTIL_THREADPOOL_H_
#define INFERNO_UTIL_THREADPOOL_H_

#include <vector>
#include <thread>
#include <mutex>

class ProgressiveRenderer;
class FrameBuffer;

class ThreadPool {
public:
	bool Ready = false;
	std::vector<std::thread*> Pool;
	std::vector<bool> ThreadStatus; // false = not done, true = done
	std::mutex ThreadLock;
	int ThreadCount = 6;
};

class RenderThreadPool : public ThreadPool {
public:
	RenderThreadPool();
	
	void SetJobs(ProgressiveRenderer* renderer, int x, int y);
	void BeginJobs();
	bool CheckAllJobs(); // false = not ready, true = ready
	void RunJobsAgain();
	void Destroy();

	void MergeBuffers(uint32_t* Framebuffer);

	std::vector<FrameBuffer*> ThreadFrameBuffers;
};

void workerThread(RenderThreadPool* threadpool, ProgressiveRenderer* renderer, int idd, int yStart, int yRange);

#endif

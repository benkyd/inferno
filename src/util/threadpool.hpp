#ifndef INFERNO_UTIL_THREADPOOL_H_
#define INFERNO_UTIL_THREADPOOL_H_

#include <vector>
#include <thread>
#include <mutex>
#include <tuple>

class ProgressiveRenderer;
class FrameBuffer;
class MapBuffer;

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
	
	void SetJobs(ProgressiveRenderer* renderer, int w, int h);
	void BeginJobs();
	bool CheckAllJobs(); // false = not ready, true = ready
	void RunJobsAgain();
	void Destroy();

	void MergeBuffers(uint32_t* framebuffer, int w, int h);

	std::vector<std::tuple<int, int>> RenderRegions; // offest, size
	MapBuffer* MappedThreadFrameBuffer;
	FrameBuffer* ThreadFrameBuffer;
};

void workerThread(RenderThreadPool* threadpool, ProgressiveRenderer* renderer, int idd, int yStart, int yRange);

#endif

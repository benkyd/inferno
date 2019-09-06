#ifndef INFERNO_DISPLAY_FRAMEBUFFER_H_
#define INFERNO_DISPLAY_FRAMEBUFFER_H_

#include "../common.hpp"
#include "../maths.hpp"

#include <mutex>

class Pixel;

class FrameBuffer {
public:
	FrameBuffer(int xres, int yres);

	void SetPixel(int x, int y, glm::vec3 p);
	void SetPixelSafe(int x, int y, glm::vec3 p);

	void DumpToFile(std::string path);

	void SetFramebuffer(uint32_t* fb);
	void ClearFramebuffer();
	uint32_t* Data;
	int XRes, YRes;
	float Gamma = 1.0f / 2.3f;


	~FrameBuffer();
};

#endif

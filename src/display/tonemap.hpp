#ifndef INFERNO_ENGINE_TONEMAP_H_
#define INFERNO_ENGINE_TONEMAP_H_

#include "../common.hpp"
#include "../maths.hpp"

#include <mutex>

class FrameBuffer;
class Pixel;

class MapBuffer {
public:
	MapBuffer(int xres, int yres);

	void SetPixel(int x, int y, glm::vec3 p);
	void SetPixelSafe(int x, int y, glm::vec3);

	void SetFramebuffer(glm::vec3* fb);
	void ClearFramebuffer();


	void ClampBasic(FrameBuffer* buffer);
	void MapBasic(FrameBuffer* buffer);


	glm::vec3* Data;
	int XRes, YRes;

	~MapBuffer();
};

#endif

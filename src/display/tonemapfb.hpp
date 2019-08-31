#ifndef INFERNO_ENGINE_TONEMAP_H_
#define INFERNO_ENGINE_TONEMAP_H_

#include "../common.hpp"
#include "../maths.hpp"

#include <mutex>

class FrameBuffer;
class Pixel;

enum LastOperation {
	OPERATION_SET,
	OPERATION_ADD,
	OPERATION_ADD_DEPTH,
	OPERATION_NONE
};

class ToneMapFrameBuffer {
public:
	ToneMapFrameBuffer(int xres, int yres);

	void SetPixel(int x, int y, glm::vec3 p);
	void SetPixelSafe(int x, int y, glm::vec3 p);
	void AddPixelSafe(int x, int y, glm::vec3 p);
	void AddPixelSafeDepth(int x, int y, glm::vec3 p);

	void SetFramebuffer(glm::vec3* fb);
	void ClearFramebuffer();


	void ClampBasic(FrameBuffer* buffer);
	void MapBasic(FrameBuffer* buffer);


	LastOperation LastOp = OPERATION_NONE;
	glm::vec3* RenderTo;
	glm::vec3* ProcData;
	int XRes, YRes;

	~ToneMapFrameBuffer();
};

#endif

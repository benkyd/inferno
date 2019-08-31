#include "tonemapfb.hpp"

#include "framebuffer.hpp"

#include "../pixel.hpp"

ToneMapFrameBuffer::ToneMapFrameBuffer(int xres, int yres) {
	XRes = xres; YRes = yres;
	RenderTo = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)RenderTo, 0, (xres * yres) * sizeof(glm::vec3));
	ProcData = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)ProcData, 0, (xres * yres) * sizeof(glm::vec3));
}

void ToneMapFrameBuffer::SetPixel(int x, int y, glm::vec3 p) {
	if (LastOp != OPERATION_SET) { ClearFramebuffer(); }
	LastOp = OPERATION_SET;
	RenderTo[y * this->XRes + x] = p;
}

void ToneMapFrameBuffer::SetPixelSafe(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		if (LastOp != OPERATION_SET) { ClearFramebuffer(); }
		LastOp = OPERATION_SET;
		RenderTo[y * this->XRes + x] = p;
	}
}

void ToneMapFrameBuffer::AddPixelSafe(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		if (LastOp != OPERATION_ADD) { ClearFramebuffer(); }
		LastOp = OPERATION_ADD;
		RenderTo[y * this->XRes + x] += p;
	}
}

void ToneMapFrameBuffer::AddPixelSafeDepth(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		if (LastOp != OPERATION_ADD_DEPTH) { ClearFramebuffer(); }
		LastOp = OPERATION_ADD_DEPTH;
		RenderTo[y * this->XRes + x] += p;
	}
}


void ToneMapFrameBuffer::SetFramebuffer(glm::vec3* fb) {
	free(ProcData);
	RenderTo = fb;
}

void ToneMapFrameBuffer::ClearFramebuffer() {
	memset((void*)RenderTo, 0, (XRes * YRes) * sizeof(glm::vec3));
}

void ToneMapFrameBuffer::ClampBasic(FrameBuffer* buffer) {
	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		buffer->SetPixelSafe(x, y, Clamp(ProcData[y * this->XRes + x], 1.0f, 0.0f));
	}
}

void ToneMapFrameBuffer::MapBasic(FrameBuffer* buffer) {
	float max = 0.0f;

	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		if (ProcData[y * this->XRes + x].r > max) max = ProcData[y * this->XRes + x].r;
		if (ProcData[y * this->XRes + x].g > max) max = ProcData[y * this->XRes + x].g;
		if (ProcData[y * this->XRes + x].b > max) max = ProcData[y * this->XRes + x].b;
	}

	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		buffer->SetPixelSafe(x, y, ProcData[y * this->XRes + x] / max);
	}
}

ToneMapFrameBuffer::~ToneMapFrameBuffer() {
	free(RenderTo);
	free(ProcData);
}

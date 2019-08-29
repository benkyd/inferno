#include "tonemap.hpp"

#include "framebuffer.hpp"

#include "../pixel.hpp"

MapBuffer::MapBuffer(int xres, int yres) {
	XRes = xres; YRes = yres;
	Data = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)Data, 0, (xres * yres) * sizeof(glm::vec3));
}

void MapBuffer::SetPixel(int x, int y, glm::vec3 p) {
	Data[y * this->XRes + x] = p;
}

void MapBuffer::SetPixelSafe(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		Data[y * this->XRes + x] = p;
	}
}

void MapBuffer::SetFramebuffer(glm::vec3* fb) {
	free(Data);
	Data = fb;
}

void MapBuffer::ClearFramebuffer() {
	memset((void*)Data, 0, (XRes * YRes) * sizeof(glm::vec3));
}

void MapBuffer::ClampBasic(FrameBuffer* buffer) {
	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		buffer->SetPixelSafe(x, y, Clamp(Data[y * this->XRes + x], 1.0f, 0.0f));
	}
}

void MapBuffer::MapBasic(FrameBuffer* buffer) {
	
}

MapBuffer::~MapBuffer() {
	free(Data);
}

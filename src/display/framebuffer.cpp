#include "framebuffer.hpp"

#include "../pixel.hpp"

FrameBuffer::FrameBuffer(int xres, int yres) {
	XRes = xres; YRes = yres;
	Data = (uint32_t*)malloc((xres * yres) * sizeof(uint32_t));
	memset((void*)Data, 0, (xres * yres) * sizeof(uint32_t));
}

void FrameBuffer::SetPixel(int x, int y, Pixel p) {
	Data[y * this->XRes + x] = p.rgb();
}

void FrameBuffer::SetPixel(int x, int y, uint32_t p) {
	Data[y * this->XRes + x] = p;
}

void FrameBuffer::SetPixel(int x, int y, glm::vec3 p) {
	Pixel pixel{ (uint8_t)(p.r * 255.0f), (uint8_t)(p.g * 255.0f), (uint8_t)(p.b * 255.0f) };
	Data[y * this->XRes + x] = pixel.rgb();
}

void FrameBuffer::SetPixelSafe(int x, int y, Pixel p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		Data[y * this->XRes + x] = p.rgb();
	}
}

void FrameBuffer::SetPixelSafe(int x, int y, uint32_t p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		Data[y * this->XRes + x] = p;
	}
}

void FrameBuffer::SetPixelSafe(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		Pixel pixel{ (uint8_t)(p.r * 255.0f), (uint8_t)(p.g * 255.0f), (uint8_t)(p.b * 255.0f) };
		Data[y * this->XRes + x] = pixel.rgb();
	}
}

void FrameBuffer::SetFramebuffer(uint32_t* fb) {
	free(Data);
	Data = fb;
}

void FrameBuffer::ClearFramebuffer() {
	memset((void*)Data, 0, (XRes * YRes) * sizeof(uint32_t));
}

FrameBuffer::~FrameBuffer() {
	free(Data);
}

#include "framebuffer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../util/stb_image_write.hpp"

#include "../pixel.hpp"

FrameBuffer::FrameBuffer(int xres, int yres) {
	XRes = xres; YRes = yres;
	Data = (uint32_t*)malloc((xres * yres) * sizeof(uint32_t));
	memset((void*)Data, 0, (xres * yres) * sizeof(uint32_t));
}

void FrameBuffer::SetPixel(int x, int y, glm::vec3 p) {
	Pixel pixel{ (uint8_t)(pow(p.r, Gamma) * 255.0f), (uint8_t)(pow(p.g, Gamma) * 255.0f), (uint8_t)(pow(p.b, Gamma) * 255.0f) };
	Data[y * this->XRes + x] = pixel.rgb();
}

void FrameBuffer::SetPixelSafe(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		Pixel pixel{ (uint8_t)(pow(p.r, Gamma) * 255.0f), (uint8_t)(pow(p.g, Gamma) * 255.0f), (uint8_t)(pow(p.b, Gamma) * 255.0f) };
		Data[y * this->XRes + x] = pixel.rgb();
	}
}

void FrameBuffer::DumpToFile(std::string path) {
	// int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
	stbi_write_png(path.c_str(), this->XRes, this->YRes, sizeof(uint32_t), this->Data, sizeof(uint32_t) * this->XRes);
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

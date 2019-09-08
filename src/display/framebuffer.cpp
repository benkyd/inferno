#include "framebuffer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../util/stb_image_write.hpp"

#include "../pixel.hpp"


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



FrameBuffer::FrameBuffer(int xres, int yres) {
	XRes = xres; YRes = yres;
	RenderData = (uint32_t*)malloc((xres * yres) * sizeof(uint32_t));
	memset((void*)RenderData, 0, (xres * yres) * sizeof(uint32_t));
	
	RenderNormalsTarget = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)RenderNormalsTarget, 0, (xres * yres) * sizeof(glm::vec3));

	RenderAlbedoTarget = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)RenderAlbedoTarget, 0, (xres * yres) * sizeof(glm::vec3));
	
	RenderTarget = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)RenderTarget, 0, (xres * yres) * sizeof(glm::vec3));

	RenderPostProcess = (glm::vec3*)malloc((xres * yres) * sizeof(glm::vec3));
	memset((void*)RenderPostProcess, 0, (xres * yres) * sizeof(glm::vec3));
}

void FrameBuffer::SetPixelSafeNormal(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		RenderNormalsTarget[y * this->XRes + x] = p;
	}
}

void FrameBuffer::SetPixelSafeAlbedo(int x, int y, glm::vec3 p) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		RenderAlbedoTarget[y * this->XRes + x] = p;
	}
}

void FrameBuffer::SetPixelSafe(int x, int y, glm::vec3 p, int mode = 0) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		if (m_lastActiveFrameBufferMode != mode) { ClearFramebuffer(); }
		m_lastActiveFrameBufferMode = mode;
		RenderTarget[y * this->XRes + x] = p;
	}
}

void FrameBuffer::AddPixelSafe(int x, int y, glm::vec3 p, int mode = 0) {
	if (x >= 0 && x < this->XRes && y >= 0 && this->YRes) {
		if (m_lastActiveFrameBufferMode != mode) { ClearFramebuffer(); }
		m_lastActiveFrameBufferMode = mode;
		RenderTarget[y * this->XRes + x] += p;
	}
}

// PostProcesses based on previous input, the tonemap mode and 
// the sample count for additive frames to average
void PostProcess(int spp, ToneMapMode mode = MODE_TONEMAP_CLAMP);

// Saves the RenderData to a file, data must first be processed
// by the render engine / the engine manager based on mode
void DumpToFile(std::string path);

// Copys the active render data to the target framebuffer,
// relies on the framebuffers to be of equal size and not
// not that
void CopyData(uint32_t* dest);

// Clears the RenderTarget and the RenderData
void ClearFramebuffer();

~FrameBuffer();


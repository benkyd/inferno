#include "framebuffer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../util/stb_image_write.hpp"

#include "../pixel.hpp"

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

void FrameBuffer::PostProcess(int& spp, ToneMapMode mode, RenderMode rendermode) {
	if (rendermode == MODE_RENDER_NORMALS || rendermode == MODE_RENDER_PATH_LENGTH) { 
		spp = 0;
		for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			RenderPostProcess[y * w + x] = src[y * w + x];
		}
		return;
	}

	if (rendermode == MODE_RENDER_PATH_BOUNCES) {
		spp++;
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++) {
				dst[y * w + x] = src[y * w + x] / (float)spp;
			}
		return;
	}

	SPP++;
	for (int y = 0; y < h; y++)
	for (int x = 0; x < w; x++) {
		dst[y * w + x] = src[y * w + x] / (float)SPP;
	}
}

void FrameBuffer::DumpToFile(std::string path) {
	// int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
	// Red and Blue channels need to be swapped
	stbi_write_png(path.c_str(), this->XRes, this->YRes, sizeof(uint32_t), this->RenderData, sizeof(uint32_t) * this->XRes);
}

void FrameBuffer::CopyData(uint32_t* dest) {
	memcpy((void*)dest, (void*)RenderData, (this->XRes * this->YRes) * sizeof(uint32_t));
}

void FrameBuffer::ClearFramebuffer() {
	memset((void*)RenderTarget, 0, (this->XRes * this->YRes) * sizeof(glm::vec3));
	memset((void*)RenderPostProcess, 0, (this->XRes * this->YRes) * sizeof(glm::vec3));
	memset((void*)RenderData, 0, (this->XRes * this->YRes) * sizeof(uint32_t));
}

FrameBuffer::~FrameBuffer() {
	free(RenderNormalsTarget);
	free(RenderAlbedoTarget);
	free(RenderTarget);
	free(RenderPostProcess);
	free(RenderData);
}


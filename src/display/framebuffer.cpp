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


	m_swapBuffer = (glm::vec3*)malloc((XRes * YRes) * sizeof(glm::vec3));
	memset((void*)m_swapBuffer, 0, (XRes * YRes) * sizeof(glm::vec3));
}

void FrameBuffer::SetPixelSafeNormal(int x, int y, glm::vec3 p) {
	RenderNormalsTarget[y * this->XRes + x] = p;
}

void FrameBuffer::SetPixelSafeAlbedo(int x, int y, glm::vec3 p) {
	RenderAlbedoTarget[y * this->XRes + x] = p;
}

void FrameBuffer::SetPixelSafe(int x, int y, glm::vec3 p, int mode) {
	if (m_lastActiveFrameBufferMode != mode) { ClearFramebuffer(); }
	m_lastActiveFrameBufferMode = mode;
	RenderTarget[y * this->XRes + x] = p;
}

void FrameBuffer::AddPixelSafe(int x, int y, glm::vec3 p, int mode) {
	if (m_lastActiveFrameBufferMode != mode) { ClearFramebuffer(); }
	m_lastActiveFrameBufferMode = mode;
	RenderTarget[y * this->XRes + x] += p;
}

void FrameBuffer::RenderPostProcessSafe(int x, int y, glm::vec3 p) {
	RenderPostProcess[y * this->XRes + x] = p;
}

void FrameBuffer::RenderSetPixelSafe(int x, int y, uint32_t p) {
	RenderData[y * this->XRes + x] = p;
}

void FrameBuffer::PostProcess(int& spp, ToneMapMode mode, RenderMode rendermode) {

}

void FrameBuffer::PostProcess(ToneMapMode mode) {
	memset((void*)m_swapBuffer, 0, (XRes * YRes) * sizeof(glm::vec3));
	
	// reinhard
	if (mode == MODE_TONEMAP_BASIC) {
	
		float max = 0.0f;

		for (int x = 0; x < XRes; x++)
		for (int y = 0; y < YRes; y++) {
			if (RenderPostProcess[y * this->XRes + x].r > max) max = RenderPostProcess[y * this->XRes + x].r;
			if (RenderPostProcess[y * this->XRes + x].g > max) max = RenderPostProcess[y * this->XRes + x].g;
			if (RenderPostProcess[y * this->XRes + x].b > max) max = RenderPostProcess[y * this->XRes + x].b;
		}

		for (int x = 0; x < XRes; x++)
		for (int y = 0; y < YRes; y++) {
			m_swapBuffer[y * this->XRes + x] = RenderPostProcess[y * this->XRes + x] / max;
		}
	
	} else if (mode == MODE_TONEMAP_CLAMP) {

		for (int x = 0; x < XRes; x++)
		for (int y = 0; y < YRes; y++) {
			m_swapBuffer[y * this->XRes + x] = Clamp(RenderPostProcess[y * this->XRes + x], 1.0f, 0.0f);
		}
	
	} else if (mode == MODE_TONEMAP_REINHARD) {

		for (int x = 0; x < XRes; x++)
		for (int y = 0; y < YRes; y++) {
			m_swapBuffer[y * this->XRes + x] = RenderPostProcess[y * this->XRes + x] / (RenderPostProcess[y * this->XRes + x] + 1.0f);
		}

	} else if (mode == MODE_TONEMAP_EXP) {

		for (int x = 0; x < XRes; x++)
		for (int y = 0; y < YRes; y++) {
			m_swapBuffer[y * this->XRes + x] = 1.0f - exp(RenderPostProcess[y * this->XRes + x] * 1.0f);
		}

	} else {
		for (int x = 0; x < XRes; x++)
		for (int y = 0; y < YRes; y++) {
			m_swapBuffer[y * this->XRes + x] = Clamp(RenderPostProcess[y * this->XRes + x], 1.0f, 0.0f);
		}
	}
	
	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		RenderPostProcess[y * this->XRes + x] = m_swapBuffer[y * this->XRes + x];
	}
}

uint32_t FrameBuffer::FinalProcess(glm::vec3 p) {
	Pixel pixel {
		(uint8_t)(pow(p.r, Gamma) * 255.0f),
		(uint8_t)(pow(p.g, Gamma) * 255.0f),
		(uint8_t)(pow(p.b, Gamma) * 255.0f)
	};
	return pixel.rgb();
}

void FrameBuffer::Ready() {
	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		uint32_t p = FinalProcess(RenderPostProcess[y * this->XRes + x]);
		RenderSetPixelSafe(x, y, p);
	}
}

void FrameBuffer::DumpToFile(std::string path) {
	// int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
	// TODO: Red and Blue channels need to be swapped
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
	free(m_swapBuffer);
}


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

	switch (mode) {
		case MODE_TONEMAP_REINHARD:
		{
			for (int x = 0; x < XRes; x++)
			for (int y = 0; y < YRes; y++) {
				m_swapBuffer[y * this->XRes + x] = RenderPostProcess[y * this->XRes + x] /
												(RenderPostProcess[y * this->XRes + x] + 1.0f);
			}
			
			break;
		}
		case MODE_TONEMAP_ACES_FILMATIC: 
		{

			static const glm::mat3 inputMat{
				{0.59719, 0.35458, 0.04823},
				{0.07600, 0.90834, 0.01566},
				{0.02840, 0.13383, 0.83777}
			};

			static const glm::mat3 outputMat{
				{ 1.60475, -0.53108, -0.07367},
				{-0.10208,  1.10813, -0.00605},
				{-0.00327, -0.07276,  1.07602}
			};

			auto ACES = [&](glm::vec3 v) -> glm::vec3 {
				glm::vec3 a = v * (v + 0.0245786f) - 0.000090537f;
				glm::vec3 b = v * (0.983729f * v + 0.4329510f) + 0.238081f;
				return a / b;
			};

			for (int x = 0; x < XRes; x++)
			for (int y = 0; y < YRes; y++) {
				glm::vec3 col = RenderPostProcess[y * this->XRes + x];
				
				col = col * inputMat;
				col = ACES(col);
				col = col * outputMat;
				col = Clamp(col, 1.0f, 0.0f);

				m_swapBuffer[y * this->XRes + x] = col;
			}

			break;
		}
		case MODE_TONEMAP_UNCHARTED2:
		{
			static const float exposure = 2.0f;
			static const glm::vec3 W = { 11.2f, 11.2f, 11.2f };

			auto Uncharted2 = [&](glm::vec3 x) -> glm::vec3 {
				float A = 0.15f;
				float B = 0.50f;
				float C = 0.10f;
				float D = 0.20f;
				float E = 0.02f;
				float F = 0.30f;
				return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
			};

			glm::vec3 white = glm::vec3{ 1.0f, 1.0f, 1.0f } / Uncharted2(W);


			for (int x = 0; x < XRes; x++)
			for (int y = 0; y < YRes; y++) {
				glm::vec3 col = RenderPostProcess[y * this->XRes + x];
				
				glm::vec3 cur = Uncharted2(col * exposure);

				col = cur * white;
				col = Clamp(col, 1.0f, 0.0f);

				m_swapBuffer[y * this->XRes + x] = col;
			}

			break;
		}
		case MODE_TONEMAP_CLAMP:
		{
			for (int x = 0; x < XRes; x++)
			for (int y = 0; y < YRes; y++) {
				m_swapBuffer[y * this->XRes + x] = Clamp(RenderPostProcess[y * this->XRes + x], 1.0f, 0.0f);
			}
			
			break;
		}
		case MODE_TONEMAP_BASIC:
		{
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
				
			break;
		}
		default:
		{
			break;
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
	// TODO: Red and Blue channels need to be swapped, no clue why, saving the framebuffer just doesnt work
	struct P {
		unsigned char r, g, b, a;
	};

	P* imageData = (P*)malloc((XRes * YRes) * sizeof(P));

	for (int x = 0; x < XRes; x++)
	for (int y = 0; y < YRes; y++) {
		uint32_t pixel = RenderData[y * this->XRes + x];
		uint8_t er = (pixel & 0x000000FF);
		uint8_t eg = (pixel & 0x0000FF00) >> 8;
		uint8_t eb = (pixel & 0x00FF0000) >> 16;
		uint8_t ea = (pixel & 0xFF000000) >> 24;

		imageData[y * this->XRes + x] = P{ (unsigned char)eb, (unsigned char)eg, (unsigned char)er, (unsigned char)ea };
	}

	stbi_write_png(path.c_str(), this->XRes, this->YRes, sizeof(P), imageData, sizeof(P) * this->XRes);
	free(imageData);
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


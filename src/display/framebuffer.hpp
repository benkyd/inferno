#ifndef INFERNO_DISPLAY_FRAMEBUFFER_H_
#define INFERNO_DISPLAY_FRAMEBUFFER_H_

#include "../common.hpp"
#include "../maths.hpp"

#include <mutex>

class Pixel;

class FrameBuffer {
public:
	FrameBuffer(int xres, int yres);

	// Normals are expected to be mapped as -1 to 1 on the RGB
	// channels, 0 to 1 is not acceptable. For maximum detail
	// the accumilation of normal maps should be preserved
	void SetPixelSafeNormal(int x, int y, glm::vec3 p);

	// Albedo values are expected to be the basic colour of the
	// first hit surface. Mapped between 0 and 1 for intensity on
	// the RGB channels
	void SetPixelSafeAlbedo(int x, int y, glm::vec3 p);

	// Sets main targeted render. Usually copied to from the thread
	// pools internal buffers 
	void SetPixelSafe(int x, int y, glm::vec3 p, int mode = 0);
	
	// Add to the render target
	void AddPixelSafe(int x, int y, glm::vec3 p, int mode = 0);

	// Set a pixel in the post processed framebuffer, ready to be corrected
	// for display gamma and to be transposed over to the data buffer
	void RenderPostProcessSafe(int x, int y, glm::vec3 p);

	// Sets a pixel on the RenderData framebuffer, ready for rendering
	// by the display or whatever mode the engine is in. the framebuffer
	// doesnt care.
	void RenderSetPixelSafe(int x, int y, uint32_t p);

	// PostProcesses based on previous input, the tonemap mode and 
	// the sample count for additive frames to average
	void PostProcess(int& spp, ToneMapMode mode = MODE_TONEMAP_CLAMP, RenderMode rendermode = MODE_RENDER_PATHTRACE);

	// Just tonemap ONLY the postprocessed framebuffer
	// memory usage warning, it will create the swap buffer
	// if it doesnt exist already
	void PostProcess(ToneMapMode mode = MODE_TONEMAP_CLAMP);

	// Finally, the pixel is ready to be rendered to the data buffer,
	// this method adjusts for gamma and scales back to do the last set
	uint32_t FinalProcess(glm::vec3 p);

	// Converts the PostProcessed Framebuffer back into a uint32_t
	// buffer and processes each pixel, scaling it by gamma
	void Ready();

	// Saves the RenderData to a file, data must first be processed
	// by the render engine / the engine manager based on mode
	void DumpToFile(std::string path);

	// Copys the active render data to the target framebuffer,
	// relies on the framebuffers to be of equal size and not
	// not that
	void CopyData(uint32_t* dest);

	// Clears the RenderTarget, Post Processed target
	// and the RenderData
	void ClearFramebuffer();

	// Render targets
	glm::vec3* RenderNormalsTarget;
	glm::vec3* RenderAlbedoTarget;
	glm::vec3* RenderTarget;
	glm::vec3* RenderPostProcess;
	
	uint32_t* RenderData;
	int XRes, YRes;
	float Gamma = 1.0f / 2.3f;
	
	~FrameBuffer();

private:
	glm::vec3* m_swapBuffer;

	int m_lastActiveFrameBufferMode;
};

#endif

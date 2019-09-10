#ifndef INFERNO_DENOISE_DENOISE_H_
#define INFERNO_DENOISE_DENOISE_H_

#include "../maths.hpp"

class Denoiser {
public:

	void SetAlbedo(glm::vec3* albedoBuffer);
	void SetNormals(glm::vec3* normalBuffer);
		
	void Denoise(glm::vec3* target, bool hdr);

private:

	bool m_hdr;

	glm::vec3* m_albedoBuffer;
	glm::vec3* m_normalBuffer;
	glm::vec3* m_targetBuffer;

};

#endif

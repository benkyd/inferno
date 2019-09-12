#ifndef INFERNO_DEFINITIONS_MATERIALS_TEXTURE_H_
#define INFERNO_DEFINITIONS_MATERIALS_TEXTURE_H_

#include "../../common.hpp"
#include "../../maths.hpp"

class Texture {
public:
	Texture();
	Texture(std::string texturePath);

	void Load(std::string texturePath);

	// if it returns a vector where all components
	// equal -1, there is no texture
	glm::vec3 Sample(glm::vec2 uv);
	glm::vec3 Sample(float u, float v);
	glm::vec3 SampleNormal(glm::vec2 uv);
	glm::vec3 SampleNormal(float u, float v);
	glm::vec3 SampleSpecular(glm::vec2 uv);
	glm::vec3 SampleSpecular (float u, float v);

	glm::vec3* Data;
	int Width, Height;
};

#endif

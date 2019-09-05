#ifndef INFERNO_DEFINITIONS_MATERIALS_TEXTURE_H_
#define INFERNO_DEFINITIONS_MATERIALS_TEXTURE_H_

#include "../../common.hpp"

class Texture {
public:
	Texture();

	void Load(std::string texturePath);

	glm::vec3 Sample(float u, float v);
	glm::vec3 SampleNormal(float u, float v);
//	glm::vec3 SampleSpecular (float u, float v);

private:

};

#endif

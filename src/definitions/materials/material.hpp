#ifndef INFERNO_DEFINITIONS_MATERIAL_H_
#define INFERNO_DEFINITIONS_MATERIAL_H_

#include "../common.hpp"
#include "../maths.hpp"

class Texture {};

class Material {
	glm::vec3 colour;
	Texture Tex;
	Texture NormalTexture;
	Texture BumpTexture;
	Texture GlossTexture;
	float BumpMultiplier;
	float Emittance;
	float Index;        // refractive index
	float Gloss;        // reflection cone angle in radians
	float Tint;         // specular and refractive tinting
	float Reflectivity; // metallic reflection
	bool Transparent;
};

#endif

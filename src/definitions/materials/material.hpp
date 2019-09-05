#ifndef INFERNO_DEFINITIONS_MATERIALS_MATERIAL_H_
#define INFERNO_DEFINITIONS_MATERIALS_MATERIAL_H_

#include "../../common.hpp"
#include "../../maths.hpp"

class Texture;

class Material {
public:
	Material();
	Material(glm::vec3 col, float specularity, float emmitance = 0.0f);

	glm::vec3 Bounce(glm::vec3 in, glm::vec3 normal);

	glm::vec3 Colour;
	Texture* Tex;
	Texture* NormalTexture;
	Texture* GlossTexture;
	float Emittance;
	float Specularity; // 1.0f = perfect reflective
	// float Index;        // refractive index
	// float Gloss;        // reflection cone angle in radians
	// float Tint;         // specular and refractive tinting
	// float Reflectivity; // metallic reflection
	bool Transparent;
	bool Emissive;
};

#endif
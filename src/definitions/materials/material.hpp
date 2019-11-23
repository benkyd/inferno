#ifndef INFERNO_DEFINITIONS_MATERIALS_MATERIAL_H_
#define INFERNO_DEFINITIONS_MATERIALS_MATERIAL_H_

#include "../../common.hpp"
#include "../../maths.hpp"

class Texture;

class Material {
public:
	Material();
	Material(glm::vec3 colour, float emittance, float Specularity, float index, float gloss, bool transparent, bool emissive);

	glm::vec3 Bounce(glm::vec3 in, glm::vec3 normal);

	glm::vec3 Colour;
	Texture* Tex = nullptr;
	Texture* NormalTexture = nullptr;
	Texture* GlossTexture = nullptr;
	float Emittance;
	float Specularity; // 1.0f = perfect reflective
	float Index;        // refractive index
	float Gloss;        // specular lobe angle in radians
	// float Tint;         // specular and refractive tinting
	// float Reflectivity; // metallic reflection
	bool Transparent;
	bool Emissive;
};

class GlossyMaterial : public Material {
public:
	GlossyMaterial(glm::vec3 colour, float shine, float gloss, float index = 1.5f)
		: Material(colour, 0.0f, shine, 1.0f, gloss, false, false) { };
};

class MatteMaterial : public Material {
public:
	MatteMaterial(glm::vec3 colour)
		: Material(colour, 0.0f, 0.0f, 1.0f, 0.0f, false, false) { };
};

#endif

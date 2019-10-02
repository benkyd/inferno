#include "material.hpp"

#include "specular.hpp"
#include "random.hpp"
#include "BRDF.hpp"

Material::Material() {

}

Material::Material(glm::vec3 colour, float emittance, float specularity, float index, float gloss, bool transparent, bool emissive) 
	: Colour(colour),
	  Emittance(emittance),
	  Specularity(specularity),
	  Index(index),
	  Gloss(gloss),
	  Transparent(transparent),
	  Emissive(emissive) {

	if (Emittance > 0.0f) { Emissive = true; }
	else { Emissive = false; }
}

glm::vec3 Material::Bounce(glm::vec3 in, glm::vec3 normal) {
	if (Specularity == 0.0f) {
		return CosineBRDF(normal);
	}

	float r;
	if (Specularity == 1.0f) {
		r = 1.0f;
	} else {
		r = rand01();
	}

	float fresnel = FresnelReflect(this, normal, in);

	if (r > fresnel) {
		return CosineBRDF(normal);
	} else {
		glm::vec3 reflect = Reflect(in, normal);

		if (Gloss == 0.0f)
			return reflect;

		return ConeBounce(reflect, Gloss);
	}
}

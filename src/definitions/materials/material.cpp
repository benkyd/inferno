#include "material.hpp"

#include "specular.hpp"
#include "random.hpp"
#include "BRDF.hpp"

Material::Material() {

}

Material::Material(glm::vec3 col, float specularity, float emittance)
	: Colour(col),
	Emittance(emittance) {
	Transparent = false;
	if (Emittance > 0.0f) { Emissive = true; }
	else { Emissive = false; }

	Specularity = specularity;
}


glm::vec3 Material::Bounce(glm::vec3 in, glm::vec3 normal) {
	if (Specularity == 0.0f) {
		return CosineBRDF(normal);
	}

	if (Specularity == 1.0f) {
		return Reflect(in, normal);
	}

	float r = rand01();

	if (r > Specularity) {
		return CosineBRDF(normal);
	} else {
		return Reflect(in, normal);
	}

}

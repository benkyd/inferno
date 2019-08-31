#include "material.hpp"

#include "BRDF.hpp"

Material::Material() {

}

Material::Material(glm::vec3 col, float emittance) 
	: Colour(col),
	  Emittance(emittance) {
	if (Emittance > 0.0f) { Emissive = true; } else { Emissive = false; }

}

glm::vec3 Material::Bounce(glm::vec3 in, glm::vec3 normal) {
	return CosineBRDF(normal);
}

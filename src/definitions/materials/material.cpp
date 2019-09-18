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

glm::vec3 ConeBounce(glm::vec3 reflectDir, float theta) {
	if (theta < EPSILON) {
		return reflectDir;
	}

	float u = rand01();
	float v = rand01();

	theta = theta * (1 - (2 * acos(u) / PI));
	float m1 = sin(theta);
	float m2 = cos(theta);
	float a = v * 2 * PI;
	glm::vec3 q = randomUnitVector();
	glm::vec3 s = glm::cross(reflectDir, q);
	glm::vec3 t = glm::cross(reflectDir, s);
	glm::vec3 d = { };
	d = d + (s * (m1 * cos(a)));
	d = d + (t * (m1 * sin(a)));
	d = d + (reflectDir * m2);
	return glm::normalize(d);
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
		glm::vec3 reflect = Reflect(in, normal);
		
		if (Gloss == 0.0f)
			return reflect;

		return ConeBounce(reflect, Gloss);
	}
}

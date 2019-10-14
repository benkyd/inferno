#include "specular.hpp"

#include "random.hpp"
#include "material.hpp"

glm::vec3 Reflect(glm::vec3 I, glm::vec3 N) {
	return I - 2 * glm::dot(I, N) * N;
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

float FresnelReflect(Material* mat, glm::vec3 normal, glm::vec3 incident) {
	float n1 = 1.0f;
	float n2 = mat->Index;

	// Schlick aproximation
	float r0 = (n1-n2) / (n1+n2);
	r0 *= r0;
	float cosX = -glm::dot(normal, incident);
	if (n1 > n2) {
		float n = n1/n2;
		float sinT2 = n*n*(1.0-cosX*cosX);
		// Total internal reflection
		if (sinT2 > 1.0)
			return 1.0;
		cosX = sqrt(1.0-sinT2);
	}
	float x = 1.0-cosX;
	float ret = r0+(1.0-r0)*x*x*x*x*x;

	ret = (mat->Specularity + (1.0 - mat->Specularity) * ret);
	return ret;
}


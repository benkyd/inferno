#include "BRDF.hpp"

#include "random.hpp"

glm::vec3 CosineBRDF(glm::vec3 normal) {
	const float TWO_PI = 2.0f * PI;

	float r0 = rand01();
	float r1 = rand01();

	glm::vec3 uu = glm::normalize(glm::cross(normal, { 0.0f, 1.0f, 1.0f }));
	glm::vec3 vv = glm::cross(uu, normal);

	float ra = sqrtf(r1);

	float rx = ra * cosf(TWO_PI * r0);
	float ry = ra * sinf(TWO_PI * r0);

	float rz = sqrtf(1.0f - r1);

	return glm::normalize(rx * uu + ry * vv + rz * normal);
}

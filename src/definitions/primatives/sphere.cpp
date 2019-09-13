#include "../ray.hpp"
#include "sphere.hpp"

bool Sphere::Intersect(Ray& ray, float& t) {
	float t0, t1; // Solutions for intersect

	glm::vec3 l = center - ray.origin;
	float tca = glm::dot(l, ray.direction);
	if (tca < 0.0f) return false;
	float d2 = glm::dot(l, l) - tca * tca;
	if (d2 > radius * radius) return false;
	float thc = sqrtf(radius * radius - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 < t1) t = t0;
	else t = t1;

	return true; 
}

glm::vec3 Sphere::SurfaceNormal(glm::vec3 hitPoint) {
	return glm::normalize(hitPoint - center);
}

glm::vec3 Sphere::SurfaceTangent(glm::vec3 normal) {
	return {};
}

glm::vec2 Sphere::TexCoords(glm::vec3 hitPoint) {
	glm::vec3 hit = hitPoint - center;
	return { (1.0f + atan2(hit.z, hit.x) / PI) * 0.5f,
		        	acos(hit.y / radius) / PI};
}

void Sphere::Translate(glm::vec3 trans) {
	center += trans;
}

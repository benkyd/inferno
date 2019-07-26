#include "sphere.hpp"
#include "ray.hpp"

bool Sphere::DoesIntersect(Ray& ray, float& t) {
	float t0, t1; // Solutions for intersect

	// glm::vec3 L = ray.origin - center;
	
	// float a = glm::dot(ray.direction, ray.direction);
	// float b = 2 * glm::dot(ray.direction, L);
	// float c = glm::dot(L, L) - radius;

	// if (!quadratic(a, b, c, t0, t1)) {
	// 	t = INFINITY;
	// 	return false;
	// };

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

	return true; // (t0 > t1 && t1 > 0.0f) ? t1 > 0.0f : t0 > 0.0f;
}

glm::vec3 Sphere::SurfaceNormal(glm::vec3 hitPoint) {
	return glm::normalize(hitPoint - center);
}

glm::vec2 Sphere::TexCoords(glm::vec3 hitPoint) {
	glm::vec3 hit = hitPoint - center;
	return { (1.0 + atan2(hit.z, hit.x) / PI) * 0.5,
			acos(hit.y / radius) / PI };
}

void Sphere::Translate(glm::vec3 trans) {
	center += trans;
}

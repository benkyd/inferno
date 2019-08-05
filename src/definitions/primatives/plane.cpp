#include "plane.hpp"
#include "../ray.hpp"

bool Plane::DoesIntersect(Ray& ray, float& t) {
	t = INFINITY;
	float dNormal = glm::dot(normal, ray.direction);
	if (dNormal > 1e-6) {
		glm::vec3 v = center - ray.origin;
		float distance = glm::dot(v, normal) / dNormal;
		if (distance >= 0.0f) {
			t = distance;
			return true;
		}
	}
	return false;
}
 
glm::vec3 Plane::SurfaceNormal(glm::vec3 hitPoint) {
    return -normal;
}

glm::vec2 Plane::TexCoords(glm::vec3 hitPoint) {
    glm::vec3 xAxis = glm::cross(normal, { 0.0f, 0.0f, 1.0f });
	if (xAxis.length() == 0.0f) xAxis = glm::cross(normal, { 0.0f, 1.0f, 0.0f });
	glm::vec3 yAxis = glm::cross(normal, xAxis);

	glm::vec3 hit = hitPoint - center;
	return { glm::dot(hit, xAxis), glm::dot(hit, yAxis) };
}

void Plane::Translate(glm::vec3 trans) {
	center += trans;
}

#ifndef INFERNO_DEFINITIONS_PRIMATIVES_SPHERE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_SPHERE_H_

#include "primative.hpp"

class Sphere : public Primative {

    Sphere(glm::vec3 center, float radius)
        : Primative(center, radius) { }

    bool DoesIntersect(Ray& ray, float& t) override;
	glm::vec3 SurfaceNormal(glm::vec3 hitPoint) override;
	glm::vec2 TexCoords(glm::vec3 hitPoint) override;
	void Translate(glm::vec3 trans) override;
};

#endif

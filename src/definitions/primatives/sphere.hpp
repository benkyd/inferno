#ifndef INFERNO_DEFINITIONS_PRIMATIVES_SPHERE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_SPHERE_H_

#include "primative.hpp"

class Sphere : public Primative {
public:
    Sphere(glm::vec3 center, float radius, Material* mat = new Material())
        : Primative(center, radius, mat) { }

    bool Intersect(Ray& ray, float& t) override;
	glm::vec3 SurfaceNormal(glm::vec3 hitPoint) override;
	glm::vec3 SurfaceTangent(glm::vec3 normal) override;
	glm::vec2 TexCoords(glm::vec3 hitPoint) override;
	void Translate(glm::vec3 trans) override;
};

#endif

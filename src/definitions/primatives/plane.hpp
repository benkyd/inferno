#ifndef INFERNO_DEFINITIONS_PRIMATIVES_PLANE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_PLANE_H_

#include "primative.hpp"

class Plane : public Primative {
public:
    Plane(glm::vec3 center, glm::vec3 normal, Material* mat = new Material())
        : Primative(center, normal, mat) { }

    bool Intersect(Ray& ray, float& t) override;
	glm::vec3 SurfaceNormal(glm::vec3 hitPoint) override;
	glm::vec3 SurfaceTangent(glm::vec3 normal) override;
	glm::vec2 TexCoords(glm::vec3 hitPoint) override;
	void Translate(glm::vec3 trans) override;
};

#endif

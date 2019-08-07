#ifndef INFERNO_DEFINITIONS_PRIMATIVES_TRIANGLE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_TRIANGLE_H_

#include "primative.hpp"

class Triangle : public Primative {
public:
    Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 n0, glm::vec3 n1, glm::vec3 n2)
        : Primative(p0, p1, p2, n0, n1, n2) { }

    bool Intersect(Ray& ray, float& t) override;
	glm::vec3 SurfaceNormal(glm::vec3 hitPoint) override;
	glm::vec2 TexCoords(glm::vec3 hitPoint) override;
	void Translate(glm::vec3 trans) override;
    glm::vec3 Midpoint();
};

#endif

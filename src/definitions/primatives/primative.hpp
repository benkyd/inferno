#ifndef INFERNO_DEFINITIONS_PRIMATIVES_PRIMATIVE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_PRIMATIVE_H_

#include "../maths.hpp"

class Ray;

enum PrimativeType {
    TYPE_NONE,
    TYPE_SPHERE,
    TYPE_PLANE,
    TYPE_TRI
};

class Primative {
public:
    // Attributes
    glm::vec3 center;
    //      Sphere
    float radius;
    //      Plane
    glm::vec3 normal;

    PrimativeType type = TYPE_NONE;

    // Sphere constructor
    Primative(glm::vec3 center, float radius) 
        : center(center), radius(radius) { 
        type = TYPE_SPHERE;
    }

    // Plane constructor
    Primative(glm::vec3 center, glm::vec3 normal) 
        : center(center), normal(normal) {
        type = TYPE_PLANE;
    }

    virtual bool DoesIntersect(Ray& ray, float& t) = 0;
	virtual glm::vec3 SurfaceNormal(glm::vec3 hitPoint) = 0;
	virtual glm::vec2 TexCoords(glm::vec3 hitPoint) = 0;
	virtual void Translate(glm::vec3 trans) = 0;
};

#endif

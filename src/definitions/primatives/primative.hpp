#ifndef INFERNO_DEFINITIONS_PRIMATIVES_PRIMATIVE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_PRIMATIVE_H_

#include "../../maths.hpp"

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
    //      Triangle
    glm::vec3 points[3];
    glm::vec3 normals[3];


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

    // Triangle constructor
    Primative(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 n0, glm::vec3 n1, glm::vec3 n2) {
		points[0] = p0; points[1] = p1; points[2] = p2;
        normals[0] = n0; normals[1] = n1; normals[2] = n2;
        type = TYPE_TRI;
    }

    virtual bool DoesIntersect(Ray& ray, float& t) = 0;
	virtual glm::vec3 SurfaceNormal(glm::vec3 hitPoint) = 0;
	virtual glm::vec2 TexCoords(glm::vec3 hitPoint) = 0;
	virtual void Translate(glm::vec3 trans) = 0;
};

#endif

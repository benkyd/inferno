#ifndef INFERNO_DEFINITIONS_PRIMATIVES_PRIMATIVE_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_PRIMATIVE_H_

#include "../materials/material.hpp"
#include "../materials/texture.hpp"

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

	Material* material = nullptr;

    PrimativeType type = TYPE_NONE;

    // Sphere constructor
    Primative(glm::vec3 center, float radius, Material* mat) 
        : center(center), radius(radius) { 
        type = TYPE_SPHERE;
		material = mat;
    }

    // Plane constructor
    Primative(glm::vec3 center, glm::vec3 normal, Material* mat)
        : center(center), normal(normal) {
        type = TYPE_PLANE;
		material = mat;
    }

    // Triangle constructor
    Primative(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 n0, glm::vec3 n1, glm::vec3 n2, Material* mat) {
		points[0] = p0; points[1] = p1; points[2] = p2;
        normals[0] = n0; normals[1] = n1; normals[2] = n2;
        type = TYPE_TRI;
		material = mat;
    }

    virtual bool Intersect(Ray& ray, float& t) = 0;
	virtual glm::vec3 SurfaceNormal(glm::vec3 hitPoint) = 0;
	virtual glm::vec2 TexCoords(glm::vec3 hitPoint) = 0;
	virtual void Translate(glm::vec3 trans) = 0;

	inline glm::vec3 Normal(glm::vec3 hitPoint) {
		if (material == nullptr) return SurfaceNormal(hitPoint);
		if (material->NormalTexture == nullptr) return SurfaceNormal(hitPoint);

		return material->NormalTexture->SampleNormal(TexCoords(hitPoint));

		// combine with surface normal
	}
};

#endif

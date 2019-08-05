#ifndef INFERNO_ACCELERATION_KD_H_
#define INFERNO_ACCELERATION_KD_H_

#include "../maths.hpp"

class Triangle;
class Ray;

class Box {
public:
	Box();
	Box(Triangle* object);

	void ExtendTriangle(Triangle* object);
	void ExtendPoint(glm::vec3 p);
	int LongestAxis();

	bool Hit(Ray* ray);
	
    glm::vec3 min;
	glm::vec3 max;
};

class KDTree {
public:
	Box bounds;

	KDTree* child0 = nullptr;
	KDTree* child1 = nullptr;

	std::vector<Triangle*> children;
};

KDTree* BuildKDTree(const std::vector<Triangle*>& triangles);

bool KDIntersect(KDTree* tree, Ray* ray, Triangle*& triMin, float& uMin, float& vMin, float& tMin);

#endif

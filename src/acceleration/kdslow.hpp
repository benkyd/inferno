#ifndef INFERNO_ACCELERATION_KDSLOW_H_
#define INFERNO_ACCELERATION_KDSLOW_H_

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
	
    glm::vec3 min = {};
	glm::vec3 max = {};
};

class KDTreeSlow {
public:
	Box bounds;

	KDTreeSlow* child0 = nullptr;
	KDTreeSlow* child1 = nullptr;

	std::vector<Triangle*> children;
};

void BuildKDTreeSlow(KDTreeSlow* tree, const std::vector<Triangle*>& triangles);
bool KDIntersectSlow(KDTreeSlow* tree, Ray* ray, Triangle*& triMin, float& tMin);

#endif

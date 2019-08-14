#ifndef INFERNO_ACCELERATION_BBOX_H_
#define INFERNO_ACCELERATION_BBOX_H_

#include "../maths.hpp"

class Ray;
class Triangle;

class BBox {
public:
	glm::vec3 vmin, vmax;
	BBox();

	void MakeEmpty();
	void Add(glm::vec3 vec);
	bool Inside(glm::vec3 v);
    bool TestIntersect(Ray& ray);
    float ClosestIntersection(Ray& ray);
	bool IntersectTriangle(Triangle& triangle);
    void Split(Axis axis, float where, BBox& left, BBox& right);
	bool IntersectWall(Axis axis, float where, const Ray& ray);
};

#endif

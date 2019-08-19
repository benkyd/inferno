#ifndef INFERNO_ACCELERATION_KD_H_
#define INFERNO_ACCELERATION_KD_H_

#include "../maths.hpp"

class Triangle;
class BBox;
class Ray;

struct KDTree {
	Axis axis; // AXIS_NONE if this is a leaf node
	float splitPos;
	
	union {
		std::vector<Triangle*>* triangles;
		KDTree* children;
	};

	void InitLeaf(const std::vector<Triangle*>& triangles);
	void InitTreeNode(Axis axis, float splitPos);
	~KDTree();
};

void BuildKDTree(KDTree* node, BBox bbox, std::vector<Triangle*>& triangleList, int depth);
bool KDIntersect(KDTree* node, BBox& bbox, Ray& ray, Triangle*& intersect, float& t);

#endif

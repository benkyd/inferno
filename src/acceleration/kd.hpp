#ifndef INFERNO_ACCELERATION_KD_H_
#define INFERNO_ACCELERATION_KD_H_

#include "../maths.hpp"

class Triangle;
class BBox;
class Ray;

struct KDTreeNode {
	Axis axis; // AXIS_NONE if this is a leaf node
	float splitPos;	
	union {
		std::vector<Triangle*>* triangles;
		KDTreeNode* children;
	};

	void InitLeaf(const std::vector<Triangle*>& triangles);
	void InitTreeNode(Axis axis, float splitPos);
	~KDTreeNode();
};	

void BuildKDTree(KDTreeNode* node, BBox bbox, std::vector<Triangle*>& triangleList, int depth);
bool KDIntersect(KDTreeNode* node, BBox& bbox, Ray& ray, Triangle*& intersect, float& t);

#endif

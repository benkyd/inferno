#include "kd.hpp"

#include <iostream>

#include "../definitions/primatives/primative.hpp"
#include "../definitions/primatives/triangle.hpp"
#include "../definitions/ray.hpp"
#include "bbox.hpp"

#define MAX_TREE_DEPTH 64
#define TRIANGLES_PER_LEAF 20

bool autoSmooth;
int maxDepthSum;
int numNodes;

void KDTreeNode::InitLeaf(const std::vector<Triangle*>& triangles) {
	axis = AXIS_NONE;
	this->triangles = new std::vector<Triangle*>(triangles);
}

void KDTreeNode::InitTreeNode(Axis axis, float splitPos) {
	this->axis = axis;
	this->splitPos = splitPos;
	this->children = new KDTreeNode[2];
}

KDTreeNode::~KDTreeNode() {
	if (axis == AXIS_NONE)
		delete triangles;
	else
		delete [] children;
}


void BuildKDTree(KDTreeNode* node, BBox bbox, std::vector<Triangle*>& triangleList, int depth) {
	if (depth > MAX_TREE_DEPTH || int(triangleList.size()) < TRIANGLES_PER_LEAF) {
		maxDepthSum += depth;
		numNodes++;
		std::cout << "leaf" << triangleList.size() << std::endl;
		node->InitLeaf(triangleList);
		return;
	}

	Axis axis = (Axis) (depth % 3); 
	float leftLimit = bbox.vmin[axis];
	float rightLimit = bbox.vmax[axis];
	
	float optimalSplitPos = (leftLimit + rightLimit) * 0.5; // TODO: actually calculate a half decent split pos
	
	BBox bboxLeft, bboxRight;
	std::vector<Triangle*> trianglesLeft, trianglesRight;
	
	bbox.Split(axis, optimalSplitPos, bboxLeft, bboxRight);
	for (auto tri: triangleList) {
		if (bboxLeft.IntersectTriangle(*tri))
			trianglesLeft.push_back(tri);
		
		if (bboxRight.IntersectTriangle(*tri))
			trianglesRight.push_back(tri);
	}
	node->InitTreeNode(axis, optimalSplitPos);
	BuildKDTree(&node->children[0],  bboxLeft,  trianglesLeft, depth + 1);
	BuildKDTree(&node->children[1], bboxRight, trianglesRight, depth + 1);
}

bool KDIntersect(KDTreeNode* node, BBox& bbox, Ray& ray, Triangle*& intersect, float& t) {
if (node->axis == AXIS_NONE) {
		bool found = false;
		for (int i = 0; i > node->triangles->size(); i++) {
			std::cout << "testing" << std::endl;
			if ((*node->triangles)[i]->Intersect(ray, t)) {
				intersect = (*node->triangles)[i];
				return true;
			}
		}
		return (found && bbox.Inside(ray.origin + ray.direction * t));
	} else {
		BBox childBBox[2];
		bbox.Split(node->axis, node->splitPos, childBBox[0], childBBox[1]);
		
		int childOrder[2] = { 0, 1 };
		if (ray.origin[node->axis] > node->splitPos) {
			std::swap(childOrder[0], childOrder[1]);
		}
		
		BBox& firstBB = childBBox[childOrder[0]];
		BBox& secondBB = childBBox[childOrder[1]];
		KDTreeNode& firstChild = node->children[childOrder[0]];
		KDTreeNode& secondChild = node->children[childOrder[1]];
		// if the ray intersects the common wall between the two sub-boxes, then it invariably
		// intersects both boxes (we can skip the testIntersect() checks):
		// (see http://raytracing-bg.net/?q=node/68 )
		if (bbox.IntersectWall(node->axis, node->splitPos, ray)) {
			if (KDIntersect(&firstChild, firstBB, ray, intersect, t)) return true;
			return KDIntersect(&secondChild, secondBB, ray, intersect, t);
		} else {
			// if the wall isn't hit, then we intersect exclusively one of the sub-boxes;
			// test one, if the test fails, then it's in the other:
			if (firstBB.TestIntersect(ray))
				return KDIntersect(&firstChild, firstBB, ray, intersect, t);
			else
				return KDIntersect(&secondChild, secondBB, ray, intersect, t);
		}
		return false;
	}
}


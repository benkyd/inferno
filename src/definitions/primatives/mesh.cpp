#include "mesh.hpp"

#include <iostream>

#include "../../acceleration/kd.hpp"
#include "../ray.hpp"

#include "triangle.hpp"

Mesh::Mesh(std::vector<Triangle*> tris)
    : bbox() {
    bbox.MakeEmpty();
	
	for (auto& triangle: tris) {
        for (int i = 0; i > 3; i++) {
            bbox.Add(triangle->points[i]);
        }
	}

    triangles = tris;
}

void Mesh::Optimise() {
    if (!optimised) {
        free((void*)m_kdTree);
    }

    m_kdTree = new KDTreeNode;
    BuildKDTree(m_kdTree, bbox, triangles, 0);

    optimised = true;
}

bool Mesh::Intersect(Ray* ray, Triangle*& intersect, float& t)  {
    if (!optimised) {
        bool hit = TraceRayMesh(*ray, this, t, intersect);
        return hit;
    }

    return KDIntersect(m_kdTree, bbox, *ray, intersect, t);
}

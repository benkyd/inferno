#include "mesh.hpp"

#include <iostream>

#include "../../acceleration/kd.hpp"
#include "../ray.hpp"

#include "triangle.hpp"

Mesh::Mesh(std::vector<Triangle*> tris) {
    triangles  = tris;
}

void Mesh::Optimise() {
    if (!optimised) {
        free((void*)m_kdTree);
    }

    m_kdTree = BuildKDTree(triangles);
    optimised = true;
}

bool Mesh::Intersect(Ray* ray, Triangle*& intersect, float& t)  {
    if (!optimised) {
        bool hit = TraceRayMesh(*ray, this, t, intersect);
        return hit;
    }

    return KDIntersect(m_kdTree, ray, intersect, t);
}

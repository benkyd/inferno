#ifndef INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_

#include <vector>

#include "../../acceleration/bbox.hpp"

class Triangle;
class KDTreeNode;
class Ray;

class Mesh {
public:
    Mesh(std::vector<Triangle*> triangles);

    void Optimise();
    bool Intersect(Ray* ray, Triangle*& intersect, float& t);

    bool optimised = false;
    std::vector<Triangle*> triangles;
private:
    KDTreeNode* m_kdTree = nullptr;
    BBox bbox;
};

#endif

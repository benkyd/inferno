#ifndef INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_

#include <vector>

class Triangle;
class KDTree;
class Ray;

class Mesh {
public:
    Mesh(std::vector<Triangle*> triangles);

    void Optimise();
    bool Intersect(Ray* ray, Triangle*& intersect, float& t);

    bool optimised = false;
    std::vector<Triangle*> triangles;
private:
    KDTree* m_kdTree = nullptr;
};

#endif

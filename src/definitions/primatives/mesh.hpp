#ifndef INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_

#include <vector>

class Triangle;

class Mesh {
    std::vector<Triangle*> triangles;
};

#endif

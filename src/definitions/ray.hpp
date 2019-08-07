#ifndef INFERNO_DEFINITIONS_RAY_H_
#define INFERNO_DEFINITIONS_RAY_H_

#include <vector>
#include "../maths.hpp"

class Mesh;
class Scene;
class Triangle;
class Primative;

class Ray {
public:
    glm::vec3 origin = {};
    glm::vec3 direction = {};
};

bool TraceRayScene(Ray ray, Scene* scene, float& t, Primative*& hit);
bool TraceRayMesh(Ray ray, Mesh* scene, float& t, Triangle*& hit);
bool TraceRayTriangles(Ray ray, std::vector<Triangle*> scene, float& t, Triangle*& hit);

#endif

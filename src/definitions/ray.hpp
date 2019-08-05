#ifndef INFERNO_DEFINITIONS_RAY_H_
#define INFERNO_DEFINITIONS_RAY_H_

#include "../maths.hpp"

class Scene;
class Primative;

class Ray {
public:
    glm::vec3 origin = {};
    glm::vec3 direction = {};
};

bool TraceRay(Ray ray, Scene* scene, float& t, Primative*& hit);

#endif

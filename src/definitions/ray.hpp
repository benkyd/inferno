#ifndef INFERNO_DEFINITIONS_RAY_H_
#define INFERNO_DEFINITIONS_RAY_H_

#include "../maths.hpp"

class Scene;

class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;
};

Ray GeneratePrimaryRay(int x, int y, Scene* scene, float xSubPix = 0.5f, float ySubPix = 0.5f);

#endif

#ifndef INFERNO_DEFINITIONS_CAMERA_H_
#define INFERNO_DEFINITIONS_CAMERA_H_

#include "../maths.hpp"

class Camera {
public:
    glm::vec3 point;
    glm::vec3 look;
    float fov;
};

#endif

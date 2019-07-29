#ifndef INFERNO_DEFINITIONS_CAMERA_H_
#define INFERNO_DEFINITIONS_CAMERA_H_

#include "../maths.hpp"

class Camera {
public:
    Camera(glm::vec3 point, glm::vec3 dir, float w, float h, float f = 500.0f);

    void Update();

    glm::vec3 point;
    glm::vec3 direction;
    glm::vec3 planeCenter;
    glm::vec3 planeDirX;
    glm::vec3 planeDirY;
    float focalLen, w, h;
};

#endif

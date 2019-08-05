#ifndef INFERNO_DEFINITIONS_CAMERA_H_
#define INFERNO_DEFINITIONS_CAMERA_H_

#include "../maths.hpp"

class Ray;

class Camera {
public:
    Camera(int width, int height);
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 right, glm::vec3 up);
    Camera(glm::vec3 position, int width, int height);

    void LookAt(glm::vec3 position, glm::vec3 sky, glm::vec3 lookAt, float angle, int width, int height);

    Ray CastRay(int x, int y, float spX = 0.5f, float spY = 0.5f);

    glm::vec3 position;
    glm::vec3 direction, right, up;
};

#endif

#include "camera.hpp"

#include "ray.hpp"

Camera::Camera(int width, int height)
    : position({0,0,0}),
      direction({0,0,1}),
      right({(float)width/(float)height,0,0}),
      up({0,1,0}),
      width(width),
      height(height) { }

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 right, glm::vec3 up)
    : position(position), direction(direction), right(right), up(up) { }

Camera::Camera(glm::vec3 position, int width, int height)
    : position(position),
      direction({0,0,1}),
      right({(float)width/(float)height,0,0}),
      up({0,1,0}),
      width(width),
      height(height) { }

void Camera::LookAt(glm::vec3 position, glm::vec3 sky, glm::vec3 lookAt, float angle, int width, int height) {
    float rightL = width / (float) height;
    float dirL = 0.5f * rightL / tan(angle / 2.0f);

    direction = glm::normalize(glm::vec3 {position.x - lookAt.x, position.y - lookAt.y, position.z - lookAt.z}) * dirL;
    right = glm::normalize(glm::cross(sky, direction)) * rightL;
    up = glm::normalize(glm::cross(direction, right));
}

Ray Camera::CastRay(int x, int y, float spX, float spY) {
    // TODO: ACTUALLY GET A WORKING CAMERA
    float camX = (((float)x + spX) / (float)width  * 2.0f - 1.0f) * getAspectRatio(width, height) * getFovAdjustment(80.0f);
    // 1.0 is taken first here as y is in the vertical
    float camY = (1.0f - ((float)y + spY) / (float)height * 2.0f) * getFovAdjustment(80.0f);
    Ray ray{ {0.0f, 0.0f, 0.0f}, {camX, camY, -1.0f} };
    ray.direction = glm::normalize(ray.direction);

    return ray;

    // glm::vec3 value = direction + (right * ((float)x + spX)) + (up * ((float)y + spY));
    // glm::normalize(value);
    // return {position, value};
}

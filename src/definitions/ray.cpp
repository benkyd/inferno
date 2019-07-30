#include "ray.hpp"

#include "camera.hpp"
#include "scene.hpp"

Ray GeneratePrimaryRay(int x, int y, Scene* scene, float xSubPix, float ySubPix) {
    Camera* cam = scene->camera;
    float dy = 1.0f;
    float dx = 1.0f;
    float px = (-(float)cam->w / 2.0f) + dx * ((float)x + xSubPix);
    float py = (-(float)cam->h / 2.0f) + dy * ((float)y + ySubPix);
    glm::vec3 p = cam->planeCenter + (cam->planeDirX * px) + (cam->planeDirY * py);
    glm::vec3 dir = glm::normalize(p - cam->point);
    return {cam->point, dir};
    // double dy = 1.0;
    // double dx = 1.0;
    // double px = (- c->width / 2.0) + dx * ((double)x + 0.5);
    // double py = (- c->height / 2.0) + dy * ((double)y + 0.5);
    // Vector3 p = vec3_add3(c->planeCenter,
    //                       vec3_mult(c->planeDirectionX, px),
    //                       vec3_mult(c->planeDirectionY, py));
    // Vector3 u_r = vec3_unit(vec3_sub(p, c->position));
    // return ray_make(c->position, u_r);
}

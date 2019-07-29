#include "ray.hpp"

#include "camera.hpp"
#include "scene.hpp"

Ray GeneratePrimaryRay(int x, int y, Scene& scene, float xSubPix, float ySubPix) {
    //     double dy = 1.0;
    // double dx = 1.0;
    // double py = (- c->height / 2.0) + dy * ((double)y + 0.5);
    // double px = (- c->width / 2.0) + dx * ((double)x + 0.5);
    // Vector3 p = vec3_add3(c->planeCenter,
    //                       vec3_mult(c->planeDirectionX, px),
    //                       vec3_mult(c->planeDirectionY, py));
    // Vector3 u_r = vec3_unit(vec3_sub(p, c->position));
    // return ray_make(c->position, u_r);
    return {};
}

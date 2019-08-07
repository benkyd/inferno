#include "triangle.hpp"
#include "../ray.hpp"

bool Triangle::Intersect(Ray& ray, float& t) {
    glm::vec3 vertex0 = points[0];
    glm::vec3 vertex1 = points[1];  
    glm::vec3 vertex2 = points[2];
    glm::vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = glm::cross(ray.direction, edge2);
    a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = ray.origin - vertex0;
    u = f * glm::dot(s, h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = glm::cross(s, edge1);
    v = f * glm::dot(ray.direction, q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    t = f * glm::dot(edge2, q);
    if (t > EPSILON) // ray intersection 
        return true;
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}
 
glm::vec3 Triangle::SurfaceNormal(glm::vec3 hitPoint) {
    return ((normals[0] + normals[1] + normals[2]) / 3.0f);
}

glm::vec2 Triangle::TexCoords(glm::vec3 hitPoint) {
    return { 0.0f, 0.0f };
}

void Triangle::Translate(glm::vec3 trans) {
    points[0] += trans;
    points[1] += trans;
    points[2] += trans;
}

glm::vec3 Triangle::Midpoint() {
    return (points[0] + points[1] + points[2]) / 3.0f;
}

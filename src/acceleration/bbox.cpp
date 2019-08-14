#include "bbox.hpp"

#include "../definitions/ray.hpp"
#include "../definitions/primatives/triangle.hpp"

BBox::BBox() {}

void BBox::MakeEmpty() {
    vmin = {+INFINITY, +INFINITY, +INFINITY};
    vmax = {-INFINITY, -INFINITY, -INFINITY};
}

void BBox::Add(glm::vec3 vec) {
    vmin.x = std::min(vmin.x, vec.x); vmax.x = std::max(vmax.x, vec.x);
    vmin.y = std::min(vmin.y, vec.y); vmax.y = std::max(vmax.y, vec.y);
    vmin.z = std::min(vmin.z, vec.z); vmax.z = std::max(vmax.z, vec.z);
}

bool BBox::Inside(glm::vec3 v) {
    return (vmin.x - 1e-6 <= v.x && v.x <= vmax.x + 1e-6 &&
            vmin.y - 1e-6 <= v.y && v.y <= vmax.y + 1e-6 &&
            vmin.z - 1e-6 <= v.z && v.z <= vmax.z + 1e-6);
}
	
bool BBox::TestIntersect(Ray& ray) {
    if (Inside(ray.origin)) return true;
    for (int dim = 0; dim < 3; dim++) {
        if ((ray.direction[dim] < 0 && ray.origin[dim] < vmin[dim]) || (ray.direction[dim] > 0 && ray.origin[dim] > vmax[dim])) continue;
        if (fabs(ray.direction[dim]) < 1e-9) continue;
        float mul = ray.rdirection[dim];
        int u = (dim == 0) ? 1 : 0;
        int v = (dim == 2) ? 1 : 2;
        float dist, x, y;
        dist = (vmin[dim] - ray.origin[dim]) * mul;
        if (dist < 0) continue;

        x = ray.origin[u] + ray.direction[u] * dist;
        if (vmin[u] <= x && x <= vmax[u]) {
            y = ray.origin[v] + ray.direction[v] * dist;
            if (vmin[v] <= y && y <= vmax[v]) {
                return true;
            }
        }

        dist = (vmax[dim] - ray.origin[dim]) * mul;
        if (dist < 0) continue;
        x = ray.origin[u] + ray.direction[u] * dist;
        if (vmin[u] <= x && x <= vmax[u]) {
            y = ray.origin[v] + ray.direction[v] * dist;
            if (vmin[v] <= y && y <= vmax[v]) {
                return true;
            }
        }
    }
    return false;
}

float BBox::ClosestIntersection(Ray& ray) {
    if (Inside(ray.origin)) return 0;
    float minDist = INFINITY;
    for (int dim = 0; dim < 3; dim++) {
        if ((ray.direction[dim] < 0 && ray.origin[dim] < vmin[dim]) || (ray.direction[dim] > 0 && ray.origin[dim] > vmax[dim])) continue;
        if (fabs(ray.direction[dim]) < 1e-9) continue;
        float mul = ray.rdirection[dim];
        float xs[2] = { vmin[dim], vmax[dim] };
        int u = (dim == 0) ? 1 : 0;
        int v = (dim == 2) ? 1 : 2;
        for (int j = 0; j < 2; j++) {
            float dist = (xs[j] - ray.origin[dim]) * mul;
            if (dist < 0) continue;
            float x = ray.origin[u] + ray.direction[u] * dist;
            if (vmin[u] <= x && x <= vmax[u]) {
                float y = ray.origin[v] + ray.direction[v] * dist;
                if (vmin[v] <= y && y <= vmax[v]) {
                    minDist = std::min(minDist, dist);
                }
            }
        }
    }
    return minDist;
}

bool BBox::IntersectTriangle(Triangle& triangle) {
    if (Inside(triangle.points[0]) || Inside(triangle.points[1]) || Inside(triangle.points[2])) return true;
    Ray ray;
    for (int i = 0; i < 3; i++) for (int j = i + 1; j < 3; j++) {
        ray.origin = triangle.points[i];
        ray.direction = triangle.points[j] - triangle.points[i];
        ray.Update();
        if (TestIntersect(ray)) {
            ray.origin = triangle.points[j];
            ray.direction = triangle.points[i] - triangle.points[j];
            ray.Update();
            if (TestIntersect(ray)) return true;
        }
    }

    glm::vec3 AB = triangle.points[1] - triangle.points[0];
    glm::vec3 AC = triangle.points[2] - triangle.points[0];

    auto thing = [] (glm::vec3 a, glm::vec3 b) -> glm::vec3 {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    };

    glm::vec3 ABcrossAC = thing(AB, AC);
    
    auto multi = [] (glm::vec3 a, glm::vec3 b) -> float {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    };

    float D = multi(triangle.points[0], ABcrossAC);

    for (int mask = 0; mask < 7; mask++) {
        for (int j = 0; j < 3; j++) {
            if (mask & (1 << j)) continue;
            ray.origin = {(mask & 1) ? vmax.x : vmin.x, (mask & 2) ? vmax.y : vmin.y, (mask & 4) ? vmax.z : vmin.z};
            glm::vec3 rayEnd = ray.origin;
            rayEnd[j] = vmax[j];
            if (signOf(multi(ray.origin, ABcrossAC - D)) != signOf(multi(rayEnd, ABcrossAC - D))) {
                ray.direction = rayEnd - ray.origin;
                ray.Update();
                float t;
                if (triangle.Intersect(ray, t)) return true;
            }
        }
    }
    return false;
}

void BBox::Split(Axis axis, float where, BBox& left, BBox& right) {
    left = *this;
    right = *this;
    left.vmax[axis] = where;
    right.vmin[axis] = where;
}

bool BBox::IntersectWall(Axis axis, float where, const Ray& ray) {
    if (fabs(ray.direction[axis]) < 1e-9) return (fabs(ray.origin[axis] - where) < 1e-9);
    int u = (axis == 0) ? 1 : 0;
    int v = (axis == 2) ? 1 : 2;
    float toGo = where - ray.origin[axis];
    float rdirInAxis = ray.rdirection[axis];

    if ((toGo * rdirInAxis) < 0) return false;
    float d = toGo * rdirInAxis;
    float tu = ray.origin[u] + ray.direction[u] * d;
    if (vmin[u] <= tu && tu <= vmax[u]) {
        float tv = ray.origin[v] + ray.direction[v] * d;
        return (vmin[v] <= tv && tv <= vmax[v]);
    }
    return false;
}


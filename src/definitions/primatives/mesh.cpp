#include "mesh.hpp"

#include <iostream>

#include "../../acceleration/accel.hpp"
#include "../ray.hpp"

#include "triangle.hpp"

Mesh::Mesh(std::vector<Triangle*> tris) {
    Triangles = tris;
}

void Mesh::Optimise(AccelerationMode mode) {
    m_accelerator = new Acceleration(mode);
    m_accelerator->Construct(Triangles);
    if (m_accelerator->Constructed) Optimised = true;
}

bool Mesh::Intersect(Ray ray, Triangle*& intersect, float& t)  {
    if (!Optimised) {
        return TraceRayMesh(ray, this, t, intersect);
    }

    return m_accelerator->Intersect(ray, intersect, t);
}

#include "mesh.hpp"

#include <iostream>

#include "../../acceleration/accel.hpp"
#include "../ray.hpp"

#include "triangle.hpp"

Mesh::Mesh(std::vector<Triangle*> tris) {
    Triangles = tris;
}

void Mesh::Optimise(AccelerationMode mode) {
	if (m_accelerator != nullptr) {
		free(m_accelerator);
	}

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

void Mesh::Translate(glm::vec3 trans) {
	for (auto& tri : Triangles)
		tri->Translate(trans);
}

void Mesh::Rotate(glm::vec3 rot) {
	// TODO: This
}

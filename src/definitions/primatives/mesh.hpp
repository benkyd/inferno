#ifndef INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_
#define INFERNO_DEFINITIONS_PRIMATIVES_MESH_H_

#include <vector>

#include "../../common.hpp"
#include "../../acceleration/bbox.hpp"

class Acceleration;
class Triangle;
class KDTreeNode;
class Ray;

class Mesh {
public:
    Mesh(std::vector<Triangle*> triangles);

    void Optimise(AccelerationMode mode = MODE_ACCELERATION_KD_SLOW);
    bool Intersect(Ray ray, Triangle*& intersect, float& t);

	void Translate(glm::vec3 trans);
	void Rotate(glm::vec3 rotate);

    bool Optimised = false;
    std::vector<Triangle*> Triangles;
private:
    Acceleration* m_accelerator = nullptr;

	glm::mat4 m_rotationMat;
};

#endif

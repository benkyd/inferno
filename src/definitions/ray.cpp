#include "ray.hpp"
#include "scene.hpp"

#include <iostream>

#include "primatives/primative.hpp"
#include "primatives/triangle.hpp"
#include "primatives/mesh.hpp"

void Ray::Update() {
	rdirection.x = fabs(direction.x) > 1e-12 ? 1.0 / direction.x : 1e12;
    rdirection.y = fabs(direction.y) > 1e-12 ? 1.0 / direction.y : 1e12;
    rdirection.z = fabs(direction.z) > 1e-12 ? 1.0 / direction.z : 1e12;
}

bool TraceRayScene(Ray ray, Scene* scene, float& t, Primative*& hit) {
	int i = 0;
	float lastDistance = INFINITY;

	for (auto& object : scene->objects) {
		float distance = INFINITY;
		if (object->Intersect(ray, distance)) {
			if (distance < lastDistance) {
				hit = object;
				lastDistance = distance;
			}
		}
	}

	for (auto& mesh : scene->meshs) {
		float distance = INFINITY;
		Triangle* triHit = nullptr;
		if (mesh->Intersect(&ray, triHit, distance)) {
			if (distance < lastDistance) {
				hit = triHit;
				lastDistance = distance;
			}
		}
	}

	t = lastDistance;
    if (lastDistance == INFINITY || hit == nullptr) return false;

	return true;
}

bool TraceRayMesh(Ray ray, Mesh* scene, float& t, Triangle*& hit) {
	float lastDistance = INFINITY;

	for (auto& object : scene->triangles) {
		float distance = INFINITY;
		if (object->Intersect(ray, distance)) {
			if (distance < lastDistance) {
				hit = object;
				lastDistance = distance;
			}
		}
	}

	t = lastDistance;
	if (lastDistance == INFINITY || hit == nullptr) return false;
	return true; 
}

bool TraceRayTriangles(Ray ray, std::vector<Triangle*> scene, float& t, Triangle*& hit) {
	float lastDistance = INFINITY;

	for (auto& object : scene) {
		float distance = INFINITY;
		if (object->Intersect(ray, distance)) {
			if (distance < lastDistance) {
				hit = object;
				lastDistance = distance;
			}
		}
	}

	t = lastDistance;
	if (lastDistance == INFINITY || hit == nullptr) return false;
	return true; 
}

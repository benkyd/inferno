#include "ray.hpp"
#include "scene.hpp"
#include "primatives/primative.hpp"

bool TraceRay(Ray ray, Scene* scene, float& t, Primative*& hit) {
	int i = 0;
	float lastDistance = INFINITY;
	int index = -1;
	for (auto& object : scene->objects) {
		float distance = INFINITY;
		if (object->DoesIntersect(ray, distance)) {
			if (distance < lastDistance) {
				index = i;
				lastDistance = distance;
			}
		}
		i++;
	}

	t = lastDistance;

    if (index == -1) return false;

    hit = scene->objects[index];

	return true;
}

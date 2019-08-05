#include "ray.hpp"
#include "scene.hpp"
#include "primatives/primative.hpp"

bool TraceRay(Ray ray, Scene* scene, float& t, float& iOfHit) {
    iOfHit = -1;

	int i = 0;
	float lastDistance = INFINITY;
	int index = -1;
	for (auto& object : scene->objects) {
		float distance = INFINITY;
		if (object->DoesIntersect(ray, distance)) {
			iOfHit = i;
			if (distance < lastDistance) {
				index = i;
				lastDistance = distance;
			}
		}
		i++;
	}

	iOfHit = index;
	t = lastDistance;

	return (iOfHit != -1);
}

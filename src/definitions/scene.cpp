#include "scene.hpp"

#include "ray.hpp"

Scene::Scene(int width, int height) {
    w = width;
    h = height;
}

glm::vec3 Scene::SampleSky(Ray ray) {
	// return { 0.9f, 0.9f, 0.9f };
	return { 0.0f, 0.0f, 0.0f };
}

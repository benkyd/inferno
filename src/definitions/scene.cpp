#include "scene.hpp"

#include "ray.hpp"

Scene::Scene(int width, int height) {
    w = width;
    h = height;
}

glm::vec3 Scene::SampleSky(Ray ray) {
	return { 10.0f, 10.0f, 10.0f };
}

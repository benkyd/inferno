#include "scene.hpp"

#include "ray.hpp"

Scene::Scene(int width, int height) {
    w = width;
    h = height;
}

glm::vec3 Scene::SampleSky(Ray ray) {
	return { 0.617f, 0.980f, 1.000f };
}

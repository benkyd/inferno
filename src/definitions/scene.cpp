#include "scene.hpp"

#include "ray.hpp"


SolidSky::SolidSky(glm::vec3 col, float intensity) {
	m_colour = col; m_intensity = intensity;
}

glm::vec3 SolidSky::Sample(Ray& ray) {
	return m_colour * m_intensity;
}

GradientSky::GradientSky(glm::vec3 up, glm::vec3 horizon, float intensity) {
	m_up = up; m_horizon = horizon; m_intensity = intensity;
}

glm::vec3 GradientSky::Sample(Ray& ray) {
	float fraction = abs(ray.direction.y) * 2.0f + 0.16f;
	fraction = clamp(fraction, 0.0f, 1.0f);
	return ((m_up - m_horizon) * fraction + m_horizon) * m_intensity;
}

Scene::Scene(int width, int height) {
    w = width;
    h = height;
}

glm::vec3 Scene::SampleSky(Ray& ray) {
	return sky->Sample(ray);
}

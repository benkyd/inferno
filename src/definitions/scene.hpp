#ifndef INFERNO_DEFINITIONS_SCENE_H_
#define INFERNO_DEFINITIONS_SCENE_H_

#include "../maths.hpp"

#include <vector>

class Primative;
class Camera;
class Mesh;
class Ray;

enum SkyType {
	//TYPE_
};

class Sky {
public:
	virtual glm::vec3 Sample(Ray& ray) = 0;
};

class SolidSky : public Sky {
public:
	SolidSky(glm::vec3 col, float intensity = 1.0f);

	glm::vec3 Sample(Ray& ray) override;
private:
	glm::vec3 m_colour;
	float m_intensity;
};

class GradientSky : public Sky {
public:
	GradientSky(glm::vec3 up, glm::vec3 horizon, float intensity = 1.0f);

	glm::vec3 Sample(Ray& ray) override;
private:
	glm::vec3 m_up;
	glm::vec3 m_horizon;
	float m_intensity;
};

class Scene {
public:
    Scene(int width, int height);
    int w, h;
	float gamma;
    Camera* camera;
    std::vector<Mesh*> meshs;
	std::vector<Primative*> objects;

	Sky* sky;
	glm::vec3 SampleSky(Ray& ray);
};

#endif

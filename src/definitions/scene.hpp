#ifndef INFERNO_DEFINITIONS_SCENE_H_
#define INFERNO_DEFINITIONS_SCENE_H_

#include "../maths.hpp"

#include <vector>

class Primative;
class Camera;
class Mesh;
class Ray;

class Scene {
public:
    Scene(int width, int height);
    int w, h;
    Camera* camera;
	float gamma;
    std::vector<Primative*> objects;
    std::vector<Mesh*> meshs;

	glm::vec3 SampleSky(Ray ray);
};

#endif

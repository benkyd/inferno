#ifndef INFERNO_ENGINE_RENDERENGINE_H_
#define INFERNO_ENGINE_RENDERENGINE_H_

#include "../common.hpp"
#include "../maths.hpp"

class Primative;
class Scene;
class Ray;

class RenderEngine {
public:
	RenderEngine();

	void SetScene(Scene* scene);
	glm::vec3 GetColour(Ray ray, int depth);

	RenderMode Mode = MODE_RENDER_NORMALS;

private:
	glm::vec3 GetNormalColour(Primative* hit, glm::vec3 hitPoint);

	Scene* m_scene = nullptr;
};

#endif

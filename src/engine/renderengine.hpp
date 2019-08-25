#ifndef INFERNO_ENGINE_RENDERENGINE_H_
#define INFERNO_ENGINE_RENDERENGINE_H_

#include "../maths.hpp"

class Scene;
class Ray;

class RenderEngine {
public:
	RenderEngine();

	void SetScene(Scene* scene);

	glm::vec3 GetColour(Ray ray, int depth);
private:
	Scene* m_scene = nullptr;
};

#endif

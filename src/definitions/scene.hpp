#ifndef INFERNO_DEFINITIONS_SCENE_H_
#define INFERNO_DEFINITIONS_SCENE_H_

#include <vector>

class Camera;
class Primative;
class Mesh;

class Scene {
public:
    Scene(int width, int height);
    int w, h;
    Camera* camera;
    std::vector<Primative*> objects;
    std::vector<Mesh*> meshs;
};

#endif

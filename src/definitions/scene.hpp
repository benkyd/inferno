#ifndef INFERNO_DEFINITIONS_SCENE_H_
#define INFERNO_DEFINITIONS_SCENE_H_

#include <vector>

class Camera;
class Primative;

class Scene {
    Camera* camera;
    std::vector<Primative*> objects;
};

#endif

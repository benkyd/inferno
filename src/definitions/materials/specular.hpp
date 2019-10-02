#ifndef INFERNO_DEFINITIONS_MATERIALS_SPECULAR_H_
#define INFERNO_DEFINITIONS_MATERIALS_SPECULAR_H_

#include "../../maths.hpp"

class Material;

glm::vec3 Reflect(glm::vec3 I, glm::vec3 N);
glm::vec3 ConeBounce(glm::vec3 reflectDir, float theta);
float FresnelReflect (Material* mat, glm::vec3 normal, glm::vec3 incident);

#endif

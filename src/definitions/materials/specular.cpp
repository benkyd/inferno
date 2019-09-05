#include "specular.hpp"

glm::vec3 Reflect(glm::vec3 I, glm::vec3 N) {
	return I - 2 * glm::dot(I, N) * N;
}

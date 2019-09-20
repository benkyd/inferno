#include "random.hpp"

#include <random>

std::default_random_engine generator;

float rand01() {
	std::uniform_real_distribution<float> distribution(0, 1);
	return distribution(generator);
}

float rand11() {
	std::uniform_real_distribution<float> distribution(-1, 1);
	return distribution(generator);
}

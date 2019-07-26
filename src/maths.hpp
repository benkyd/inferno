#ifndef INFERNO_MATHS_H_
#define INFERNO_MATHS_H_

#include <glm/glm.hpp>
#include <algorithm>
#include <math.h>

const float DEG2RAD = 0.01745329251994329576923690768f;
const float RAD2DEG = 57.2957795130823208767981548141f;
const float      PI = 3.14159265358979323846264338327f;
const float EPSILON = 0.00001000000000000000000000000f;


inline float fastDegreetoRadian(const float Degree) {
	return (Degree * DEG2RAD);
}

inline float fastRadianToDegree(const float Radian) {
	return (Radian * RAD2DEG);
}

inline float getFovAdjustment(const float fov) {
	return tanf(fov * PI / 360.0f);
}

inline float getAspectRatio(const float w, const float h) {
	return (float)w / (float)h;
}

// (-b += sqrt(b^2-4ac)) / 2a
inline bool quadratic(float a, float b, float c, float& x0, float& x1) {
	float discr = b * b - 4.0f * a * c;
	if (discr < 0.0f) return false;
	else if (discr == 0.0f) x0 = x1 = -0.5f * b / a;
	else {
		float q = (b > 0.0f) ?
			-0.5f * (b + sqrtf(discr)) :
			-0.5f * (b - sqrtf(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}

inline float clamp(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

inline void clamp(glm::vec3& col, float lower, float upper) {
	clamp(col.r, lower, upper);
	clamp(col.g, lower, upper);
	clamp(col.b, lower, upper);
}

inline float modulo(float x) {
	return x - std::floor(x);
}


#endif

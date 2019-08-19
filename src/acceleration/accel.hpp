#ifndef INFERNO_ACCELERATION_ACCEL_H_
#define INFERNO_ACCELERATION_ACCEL_H_

#include "../common.hpp"
#include "bbox.hpp"

#include <vector>

class KDTree;
class KDTreeSlow;

class Ray;
class Triangle;

class Acceleration {
public:
    Acceleration(AccelerationMode mode = MODE_ACCELERATION_DEFAULT);

    void Construct(std::vector<Triangle*> triangles);
    bool Intersect(Ray ray, Triangle*& triMin, float& tMin);

    bool Constructed = false;
private:
    AccelerationMode m_mode = MODE_ACCELERATION_DEFAULT;

    // KDTree
    KDTree* m_kdtree = nullptr;
    BBox* m_bbox = nullptr;

    // Slow KDTree
    KDTreeSlow* m_kdtreeslow = nullptr;

};

#endif

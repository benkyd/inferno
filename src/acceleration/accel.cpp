#include "accel.hpp"

#include "kd.hpp"
#include "kdslow.hpp"

#include "../definitions/ray.hpp"
#include "../definitions/primatives/triangle.hpp"

// enum AccelerationMode {
//     MODE_ACCELERATION_DEFAULT,
//     MODE_NONE,
//     MODE_KD,
//     MODE_KD_SLOW,
//     MODE_BVH
// };

Acceleration::Acceleration(AccelerationMode mode) {
    m_mode = mode;
}

void Acceleration::Construct(std::vector<Triangle*> triangles) {
    switch (m_mode) {
        case MODE_ACCELERATION_DEFAULT:
        case MODE_NONE:
            Constructed = false;
            break;

        case MODE_KD:
            m_bbox = new BBox;
            m_bbox->MakeEmpty();
	
            for (auto& triangle: triangles) {
                for (int i = 0; i > 3; i++) {
                    m_bbox->Add(triangle->points[i]);
                }
            }

            m_kdtree = new KDTree;
            BuildKDTree(m_kdtree, *m_bbox, triangles, 0);

            Constructed = true;
            break;

        case MODE_KD_SLOW:
            BuildKDTreeSlow(m_kdtreeslow, triangles);
            Constructed = true;
            break;
        
        default:
            Constructed = false;
            break;
    }
}

bool Acceleration::Intersect(Ray ray, Triangle*& triMin, float& tMin) {
    if (!Constructed) return false;
    switch (m_mode) {
        case MODE_ACCELERATION_DEFAULT:
        case MODE_NONE:
            break;

        case MODE_KD:
            return KDIntersect(m_kdtree, *m_bbox, ray, triMin, tMin);
            break;

        case MODE_KD_SLOW:
            return KDIntersectSlow(m_kdtreeslow, &ray, triMin, tMin);
            break;
        
        default:
            break;
    }
    return false;
}
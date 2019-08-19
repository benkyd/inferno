#include "kdslow.hpp"

#include <iostream>
#include <algorithm>

#include "../definitions/primatives/primative.hpp"
#include "../definitions/primatives/triangle.hpp"
#include "../definitions/ray.hpp"

Box::Box() {
    return;
}

Box::Box(Triangle* object) {
    min.x = std::numeric_limits<float>::max();
    min.y = std::numeric_limits<float>::max();
    min.z = std::numeric_limits<float>::max();

    max.x = std::numeric_limits<float>::lowest();
    max.y = std::numeric_limits<float>::lowest();
    max.z = std::numeric_limits<float>::lowest();

    ExtendTriangle(object);
}

void Box::ExtendTriangle(Triangle* object) {
    ExtendPoint(object->points[0]);
    ExtendPoint(object->points[1]);
    ExtendPoint(object->points[2]);
}

void Box::ExtendPoint(glm::vec3 p) {
    if (p.x < min.x) min.x = p.x;
    if (p.y < min.y) min.y = p.y;
    if (p.z < min.z) min.z = p.z;

    if (p.x > max.x) max.x = p.x;
    if (p.y > max.y) max.y = p.y;
    if (p.z > max.z) max.z = p.z;
}

int Box::LongestAxis() {
    float diff_x = fabsf(max.x - min.x);
    float diff_y = fabsf(max.y - min.y);
    float diff_z = fabsf(max.z - min.z);

    if (diff_x > diff_y && diff_x > diff_z){
        return 0;
    } else if (diff_y > diff_z) {
        return 1;
    } else {
        return 2;
    }
}

bool Box::Hit(Ray* ray) {
    if (ray->origin.x >= min.x && ray->origin.x < max.x &&
        ray->origin.y >= min.y && ray->origin.y < max.y &&
        ray->origin.z >= min.z && ray->origin.z < max.z) {
        return true;
    }

    float dirfrac_x = 1.0f / ray->direction.x;
    float dirfrac_y = 1.0f / ray->direction.y;
    float dirfrac_z = 1.0f / ray->direction.z;

    float t1 = (min.x - ray->origin.x) * dirfrac_x;
    float t2 = (max.x - ray->origin.x) * dirfrac_x;
    float t3 = (min.y - ray->origin.y) * dirfrac_y;
    float t4 = (max.y - ray->origin.y) * dirfrac_y;
    float t5 = (min.z - ray->origin.z) * dirfrac_z;
    float t6 = (max.z - ray->origin.z) * dirfrac_z;

    float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    if (tmax < 0.0f) {
        return false;
    }

    if (tmin > tmax) {
        return false;
    }

    return tmin > 0.0f;
}

void BuildKDTreeSlow(KDTreeSlow*& node, const std::vector<Triangle*>& triangles) {
	node = new KDTreeSlow();

	node->children = triangles;

	if (triangles.size() == 0)
		return;

	if (triangles.size() == 1) {
		node->bounds = Box(triangles[0]);

		node->child0 = new KDTreeSlow();
		node->child1 = new KDTreeSlow();

		node->child0->children = std::vector<Triangle*>();
		node->child1->children = std::vector<Triangle*>();

		return;
	}

	node->bounds = Box(triangles[0]);

	for (int i = 1; i < triangles.size(); i++) {
		node->bounds.ExtendTriangle(triangles[i]);
	}

	glm::vec3 midpoint = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < triangles.size(); i++) {
		midpoint = midpoint + ((triangles[i]->Midpoint()) * (1.0f / float(triangles.size())));
	}

	std::vector<Triangle*> bucket0;
	std::vector<Triangle*> bucket1;

	int axis = node->bounds.LongestAxis();

	for (int i = 0; i < triangles.size(); i++) {
		glm::vec3 temp_midpoint = triangles[i]->Midpoint();

		if (axis == 0) {
			if (midpoint.x >= temp_midpoint.x) {
				bucket1.push_back(triangles[i]);
			}
			else {
				bucket0.push_back(triangles[i]);
			}
		} else if (axis == 1) {
			if (midpoint.y >= temp_midpoint.y) {
				bucket1.push_back(triangles[i]);
			} else {
				bucket0.push_back(triangles[i]);
			}
		} else {
			if (midpoint.z >= temp_midpoint.z) {
				bucket1.push_back(triangles[i]);
			} else {
				bucket0.push_back(triangles[i]);
			}
		}
	}
	
	if (bucket0.size() == 0 && bucket1.size() > 0) {
		bucket0 = bucket1;
	}

	if (bucket1.size() == 0 && bucket0.size() > 0) {
		bucket1 = bucket0;
	}

	int matches = 0;

	for (int i = 0; i < bucket0.size(); i++) {
		for (int j = 0; j < bucket1.size(); j++) {
			if (bucket0[i] == bucket1[j]) {
				matches++;
			}
		}
	}

	float threshold = 0.5f;

	if ((float)matches / float(bucket0.size()) < threshold &&
		(float)matches / float(bucket1.size()) < threshold) {
		BuildKDTreeSlow(node->child0, bucket0);
		BuildKDTreeSlow(node->child1, bucket1);
	} else {
		node->child0 = new KDTreeSlow();
		node->child1 = new KDTreeSlow();

		node->child0->children = std::vector<Triangle*>();
		node->child1->children = std::vector<Triangle*>();
	}
}

bool KDIntersectSlow(KDTreeSlow* kd_tree1, Ray* ray, Triangle*& triangle_min, 
                 float& t_min) {
    
	if (kd_tree1->bounds.Hit(ray) > 0.0f) {
		if (kd_tree1->child0->children.size() > 0 ||
			kd_tree1->child1->children.size() > 0) {
			bool a = KDIntersectSlow(kd_tree1->child0, ray, triangle_min, t_min);
			bool b = KDIntersectSlow(kd_tree1->child1, ray, triangle_min, t_min);

			return a || b;
		} else {
			bool did_hit_any = false;

			for (int i = 0; i < kd_tree1->children.size(); i++) {
				Triangle* triangle1 = kd_tree1->children[i];

                float t_prime;
                bool hit = triangle1->Intersect(*ray, t_prime);

				if (t_prime > 0.0f && t_prime < t_min) {
					did_hit_any = true;

					t_min = t_prime;

					triangle_min = triangle1;
				}
			}

			return did_hit_any;
		}
	}

	return false;
}

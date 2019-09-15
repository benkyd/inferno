#include "assetloader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cpp
#include "tiny_obj_loader.hpp"

#include "../definitions/materials/material.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/primatives/triangle.hpp"
#include "../maths.hpp"

glm::vec3 getNormal(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) {
    glm::vec3 u = p1 - p0;
    glm::vec3 v = p2 - p0;

    glm::vec3 normal;
    normal.x = u.y * v.z - u.z * v.y;
    normal.y = u.z * v.x - u.x * v.z;
    normal.z = u.x * v.y - u.y * v.x;

	return normal;
}

std::vector<Triangle*> LoadTrianglesBasic(std::string path, std::string basePath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn, err;

	bool canLoad = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str(), basePath.c_str());

	if (!err.empty() || !canLoad) {
		std::cerr << "Cannot load obj: '" << path << "': " << err << std::endl;
        exit(0);
	}

	if (!warn.empty()) {
		std::cerr << "Warning from obj loader while loading obj: '" << path << "': " << warn << std::endl;
	}

    std::vector<Triangle*> triangles;

    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];
			if (fv == 3) {
				tinyobj::real_t avx[3];
				tinyobj::real_t avy[3];
				tinyobj::real_t avz[3];

				tinyobj::real_t anx[3];
				tinyobj::real_t any[3];
				tinyobj::real_t anz[3];

				for (size_t v = 0; v < fv; v++) {
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					avx[v] = attrib.vertices[3 * idx.vertex_index + 0];
					avy[v] = attrib.vertices[3 * idx.vertex_index + 1];
					avz[v] = attrib.vertices[3 * idx.vertex_index + 2];

					anx[v] = attrib.normals[3 * idx.normal_index + 0];
					any[v] = attrib.normals[3 * idx.normal_index + 1];
					anz[v] = attrib.normals[3 * idx.normal_index + 2];
				}

				// tinyobj::material_t material = materials[shapes[s].mesh.material_ids[f]];

				// Material* mat = new Material({ material.diffuse[0], material.diffuse[1], material.diffuse[2] }, 0.6f, material.illum);
				Material* mat = new Material({ 0.717f, 0.792f, 0.474 }, 0.5f);
				//Material* mat = new Material({ 0.8, 0.8f, 0.8f });

                    // glm::vec3 normal = getNormal(
                    //     {avx[0], avy[0], avz[0]},
                    //     {avx[1], avy[1], avz[1]},
                    //     {avx[2], avy[2], avz[2]}
                    // );

                    Triangle* tmp = new Triangle {
                        {avx[0], avy[0], avz[0]},
                        {avx[1], avy[1], avz[1]},
                        {avx[2], avy[2], avz[2]},

                        // normal, normal, normal

                        {anx[0], any[0], anz[0]},
                        {anx[1], any[1], anz[1]},
                        {anx[2], any[2], anz[2]},

						mat,
                    };

                    triangles.push_back(tmp);
                }
            index_offset += fv;
        }
    }

    return triangles;
}

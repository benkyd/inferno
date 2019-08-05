#include "progressiverenderer.hpp"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cpp
#include "../util/tiny_obj_loader.hpp"

#include "../common.hpp"
#include "../pixel.hpp"
#include "../display/displayinterface.hpp"

#include "../definitions/primatives/primative.hpp"
#include "../definitions/primatives/triangle.hpp"
#include "../definitions/camera.hpp"
#include "../definitions/scene.hpp"
#include "../definitions/ray.hpp"

ProgressiveRenderer::ProgressiveRenderer() {
    
}

void ProgressiveRenderer::Init(DisplayInterface* interface, Scene* scene) {
    m_interface = interface;
    m_scene = scene;
}

glm::vec3 getNormal(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) {
    glm::vec3 u = p1 - p0;
    glm::vec3 v = p2 - p0;

    glm::vec3 normal;
    normal.x = u.y * v.z - u.z * v.y;
    normal.y = u.z * v.x - u.x * v.z;
    normal.z = u.x * v.y - u.y - v.x;

	return normal;
}

std::vector<Primative*> loadTriangles(std::string path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn, err;

	bool canLoad = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

	if (!err.empty() || !canLoad) {
		std::cerr << "Cannot load obj '" << path << "': " << err << std::endl;
        exit(0);
	}

	if (!warn.empty()) {
		std::cerr << "Warning from obj loader while loading obj '" << path << "': " << warn << std::endl;
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

                    tinyobj::material_t material = materials[shapes[s].mesh.material_ids[f]];

                    // glm::vec3 normal = getNormal({avx[0], avy[0], avz[0]},
 					// 			                 {avx[1], avy[1], avz[1]},
 					// 		                	 {avx[2], avy[2], avz[2]});

                    Triangle* tmp = new Triangle {
								{avx[0], avy[0], avz[0]},
								{avx[1], avy[1], avz[1]},
								{avx[2], avy[2], avz[2]},

                                {anx[0], any[0], anz[0]},
								{anx[1], any[1], anz[1]},
								{anx[2], any[2], anz[2]},
                    };

                    triangles.push_back(tmp);
                }
            index_offset += fv;
        }
    }

    std::vector<Primative*> objects;

    for (const auto& triangle : triangles)
        objects.push_back(triangle);

    return objects;
}


void ProgressiveRenderer::Render() {

    while (m_interface->Active) {

        // Take input
        SDL_Event e;
        while (SDL_PollEvent(&e)) 
            if (e.type == SDL_QUIT) m_interface->Close();

		#pragma omp parallel for schedule(dynamic)
        for (int x = 0; x < m_scene->w; x++)
        for (int y = 0; y < m_scene->h; y++) {
            Ray ray = m_scene->camera->CastRay(x, y);
            
            float t, i;
            bool didhit = TraceRay(ray, m_scene, t, i);
            if (!didhit) {
                m_interface->SetPixelSafe(x, y, 0xFFFFFF);
                continue;
            }
    
            Primative* hit = m_scene->objects[i];

            if (hit->type == TYPE_SPHERE) {
                m_interface->SetPixelSafe(x, y, 0xFFFF00);
            }

        }

        // Swap framebuffers
        m_interface->Update();
    }
}

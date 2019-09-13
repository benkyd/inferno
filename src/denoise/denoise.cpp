#include "denoise.hpp"

Denoiser::Denoiser() {

}

void Denoiser::SetAlbedo(glm::vec3* albedoBuffer) {
    m_albedoBuffer = albedoBuffer;
}

void Denoiser::SetNormals(glm::vec3* normalBuffer) {
    m_normalBuffer = normalBuffer;
}

void Denoiser::Denoise(glm::vec3* target, bool hdr) {
    m_targetBuffer = target; m_hdr = hdr;
}


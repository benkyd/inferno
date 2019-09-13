#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../util/stb_image.hpp"
#include "../../util/stb_image_write.hpp"

#include "../../common.hpp"

Texture::Texture() {

}

Texture::Texture(std::string texturePath) {
	Load(texturePath);
}

void Texture::Load(std::string texturePath) {
	struct P {
		unsigned char r, g, b, a;
	};

	Width = 0; Height = 0;
	int channels = 0;

	P* imageData = (P*)stbi_load(texturePath.c_str(), &Width, &Height, &channels, 4);

	Data = new glm::vec3[Width * Height];

	for (int x = 0; x < Width; x++)
	for (int y = 0; y < Height; y++) {
		P p = imageData[y * Width + x];
		Data[y * Width + x] = {(float)p.r / 255.0f, 
							   (float)p.g / 255.0f,
							   (float)p.b / 255.0f };
	}
}

glm::vec3 Texture::Sample(glm::vec2 uv) {
	return Sample(uv.x, uv.y);
}

glm::vec3 Texture::Sample(float u, float v) {
	u = u * Width;
	v = v * Height;
	u = floor(u - floor(u / (float)Width) * (float)Width);
	v = floor(v - floor(v / (float)Height) * (float)Height);

	return Data[(int)(v * Width + u)];
}

glm::vec3 Texture::SampleNormal(glm::vec2 uv) {
	return SampleNormal(uv.x, uv.y);
}

glm::vec3 Texture::SampleNormal(float u, float v) {
	glm::vec3 c = Sample(u, v);
	glm::vec3 s = { c.r * 2.0f - 1.0f, c.g * 2.0f - 1.0f, c.b * 2.0f - 1.0f };
	return glm::normalize(s);
}

glm::vec3 Texture::SampleSpecular(glm::vec2 uv) {
	return SampleSpecular(uv.x, uv.y);
}

glm::vec3 Texture::SampleSpecular(float u, float v) {
	return {};

}

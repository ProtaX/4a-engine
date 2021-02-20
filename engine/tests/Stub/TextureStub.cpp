#include "Texture.hpp"

namespace fae {

rgba_t *sampleData;

Texture::Texture(int force_channels) noexcept { sampleData = new rgba_t[1]; }

Texture::Texture(const std::string &path, int force_channels) { sampleData = new rgba_t[1]; }

Texture::~Texture() { delete[] sampleData; }

int Texture::GetH() const { return 1; }

int Texture::GetW() const { return 1; }

rgba_t * Texture::GetPixelData() const { return sampleData; }

GLuint Texture::GetTargetN() const { return 0; }

void Texture::SetForceChannels(int force_channels) {}

bool Texture::LoadImageA(const std::string &path) { return true; }

}

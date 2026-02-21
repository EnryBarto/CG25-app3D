#include "Texture.h"

Texture::Texture(const char* name, const char* path) {
	this->programId = TextureMaker::loadTexture(path, 0);
	this->name = std::string(name);
}

Texture::Texture(const char* name, vector<string> facesPath) {
	this->programId = TextureMaker::loadCubemap(facesPath, 0);
	this->name = std::string(name);
}

Texture::~Texture() {
	glDeleteTextures(1, &this->programId);
}

std::string Texture::getName() {
	return name;
}

GLuint Texture::getProgramId() {
	return programId;
}
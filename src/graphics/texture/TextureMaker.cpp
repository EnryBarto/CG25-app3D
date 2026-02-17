#define STB_IMAGE_IMPLEMENTATION
#include "TextureMaker.h"

GLuint TextureMaker::loadTexture(const char* path, int flip) {
	GLuint textureId;

	glGenTextures(1, &textureId);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (!data) {
		cerr << "Texture failed to load at path: " << path << endl;
		stbi_image_free(data);
		return 0;
	}

	GLenum format;

	switch (nrComponents) {
		case 1: format = GL_RED; break;
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		default:
			cerr << "Invalid texture num components: " << nrComponents << endl;
			stbi_image_free(data);
			return 0;
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	return textureId;
}

GLuint TextureMaker::loadCubemap(vector<string> facesPath, int flip) {
	GLuint textureId;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	int width, height, nrChannels;
	for (int i = 0; i < facesPath.size(); i++) {

		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(facesPath[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		} else {
			cerr << "Cubemap tex failed to load at path: " << facesPath[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureId;
}
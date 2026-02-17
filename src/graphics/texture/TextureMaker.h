#pragma once

#include "../../libs.h"
#include <stb_image/stb_image.h>

class TextureMaker {
	public:
		static GLuint loadTexture(const char* path, int flip);
		static GLuint loadCubemap(vector<string> facesPath, int flip);
};
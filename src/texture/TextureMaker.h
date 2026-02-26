#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>

using namespace std;

class TextureMaker {
	public:
		static GLuint loadTexture(const char* path, int flip);
		static GLuint loadCubemap(vector<string> facesPath, int flip);
};
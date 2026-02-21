#pragma once

#include <string>
#include "../../settings.h"
#include "TextureMaker.h"

class Texture {
	public:
		Texture(const char* name, const char* path);
		Texture(const char* name, vector<string> facesPath);
		~Texture();
		std::string getName();
		GLuint getProgramId();

	private:
		std::string name;
		GLuint programId;
};
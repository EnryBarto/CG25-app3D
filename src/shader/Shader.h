#pragma once

#include <string>
#include <glad/glad.h>

#include "ShaderMaker.h"
#include "../utils/constants.h"

class Shader {
    public:
		Shader(const char* name, const char* vertexShader, const char* fragmentShader);
		~Shader();
		std::string getName();
		GLuint getProgramId();

	private:
		std::string name;
		GLuint programId;
};
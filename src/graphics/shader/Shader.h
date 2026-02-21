#pragma once

#include <string>
#include "../../settings.h"
#include "ShaderMaker.h"

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
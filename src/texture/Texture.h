#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>

using namespace std;

class Texture {
	public:
		Texture(const char* name, const char* path);
		Texture(const char* name, vector<string> facesPath);
		~Texture();
		string getName();
		void setName(std::string name);
		GLuint getProgramId();

	private:
		string name;
		GLuint programId;
};
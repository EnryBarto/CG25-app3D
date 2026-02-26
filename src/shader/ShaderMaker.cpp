#include "ShaderMaker.h"

#include <iostream>

#pragma warning(disable:4996)
char* ShaderMaker::readShaderSource(const char* shaderFile) {
	FILE* fp = fopen(shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

GLuint ShaderMaker::createProgram(char* vertexfilename, char *fragmentfilename) {
 
	int success;
	char infoLog[512];

    // Create shader objects
    // Read vertex shader source
	GLchar* VertexShader = readShaderSource(vertexfilename);
    // Print the VERTEX SHADER code to the console
    //cout << VertexShader;

    // Generate an ID for the vertex shader
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    // Associate the shader source with the shader object
    glShaderSource(vertexShaderId, 1, (const char**)&VertexShader, NULL);
    // Compile the vertex shader
    glCompileShader(vertexShaderId); 
	
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

    // Read fragment shader source
    const GLchar* FragmentShader = readShaderSource(fragmentfilename);
    // Print the FRAGMENT SHADER code to the console
    //cout << FragmentShader;

    // Generate an ID for the fragment shader
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, (const char**)&FragmentShader, NULL);
    // Compile the fragment shader
    glCompileShader(fragmentShaderId);
	 
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
 
    // Create a program object and attach the compiled shaders
	GLuint programId = glCreateProgram();

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	
	// Validate linking
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Clean up shader objects after linking it to the program
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}

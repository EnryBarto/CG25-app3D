#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

out vec3 Normal;
out vec3 Position;
 
void main() {
	gl_Position = Projection * View * Model * vec4(aPos,1.0);

	// Transform to WCS
	Normal = mat3(transpose(inverse(Model))) * aNormal;
	Position = vec3(Model * vec4(aPos, 1.0));
} 
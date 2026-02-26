#version 330 core

uniform vec3 ViewPos;

in vec3 Normal;
in vec3 Position;
 
uniform samplerCube cubemap;
out vec4 FragColor;

void main() {
     vec3 V = normalize(Position-ViewPos);      // View vector
     vec3 R = reflect(V, normalize(Normal));    // Reflection vector
     FragColor = texture(cubemap, R);           // Sample the cubemap with the reflection vector
}
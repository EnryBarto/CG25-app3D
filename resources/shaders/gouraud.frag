#version 330 core

// UNIFORM VARIABLES
uniform sampler2D uTexture;
uniform bool uUseTexture;

// SHADER INPUT (from the vertex shader)
in vec4 ourColor;
in vec2 vTexCoord;

// SHADER OUTPUT
out vec4 FragColor;

void main() {
    FragColor = ourColor;
 
    // Apply texture if it's set
    if (uUseTexture) {
        FragColor *= texture(uTexture, vTexCoord);
    }
}

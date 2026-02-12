#version 330 core
in vec4 ourColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform bool uUseTexture;

out vec4 FragColor;

void main()
{
    vec4 baseColor = ourColor;
 
    if (uUseTexture) {
        baseColor *= texture(uTexture, vTexCoord);
    }
  

    FragColor = baseColor;
}

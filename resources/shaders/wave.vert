#version 330 core

// NB: THE VALUE CAN MAKE THE SHADER LINKING FAIL: IF SO, LOWER IT
#define MAX_LIGHTS 5 // Keep the value updated with the cpp code and other shaders

// Structure representing a point light
struct PointLight {
	vec3 position;
	vec3 color;
	float power;
};

// Structure holding material informations
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Per-vertex data taken from VBO
layout (location = 0) in vec3 aPos;     // Vertex position
layout (location = 1) in vec4 aColor;   // Vertex color
layout (location = 2) in vec3 vertexNormal; // Normal vectors
layout (location = 3) in vec2 texCoord; // Texture coordinates

// UNIFORM VARIABLES
uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;
uniform vec3 ViewPos;
uniform int numLights;  // Number of lights really used
uniform float time = 0.5;
uniform Material material; // Material propreties
uniform bool uUseBlinnPhong; // True if BlinnPhong model is used, false if Phong
uniform PointLight lights[MAX_LIGHTS]; // Propreties of each light in the scene

float ambientLightIntensity = 0.1;

// SHADER OUTPUTS TO THE FRAGMENT
out vec4 ourColor;
out vec2 vTexCoord;

void main() {
    // Transform vertices from object/model space (aPos) to world/view/projection space.
    // The vertex is first transformed by Model (object->world), then by View, and finally
    // by Projection to produce clip space coordinates in the range [-1, 1].
    
    // Displace the vertex in Y using a time-dependent function
    vec4 v = vec4(aPos, 1.0);
    v.y = sin(80.0 * v.x + time) * cos(8.5 * aPos.y + time);

    gl_Position = Projection * View * Model * v;

    // Transform the displaced vertex position into view space (use the modified position `v`)
    vec4 eyePosition = View * Model * v;

    // ----- AMBIENT COMPONENT -----
    vec3 ambient = ambientLightIntensity * material.ambient;

    ourColor = vec4(0, 0, 0, 1);

    // Transform the vertex normal into view space
    vec3 N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);

    for (int i = 0; i < numLights; i++) {

        // Transform the light position into view space
        vec4 eyeLightPos = View * vec4(lights[i].position, 1.0);

        // Compute the light direction L,  and view direction V
        vec3 V = normalize(ViewPos - eyePosition.xyz);
        vec3 L = normalize((eyeLightPos - eyePosition).xyz);

        // ----- DIFFUSE COMPONENT -----
        float cos_theta = max(dot(L, N), 0);
        vec3 diffuse = lights[i].color * cos_theta * material.diffuse;
        
        // ----- SPECULAR COMPONENT -----
        float cos_alfa;
        // Changes the calculation of specular reflection of light based on the chosen lighting model 
        if (uUseBlinnPhong) {
            // Compute Halfway Vector (Vector halfway between the direction of view and the direction of light)
            vec3 H = normalize(L + V); 
            cos_alfa = pow(max(dot(H, N), 0), material.shininess);
        } else {
            // Compute reflection direction R (light direction L compared to normal N)
            vec3 R = normalize(reflect(-L, N));
            cos_alfa = pow(max(dot(V, R), 0), material.shininess);
        }
        vec3 specular = lights[i].color * cos_alfa * material.specular;

        ourColor += vec4(ambient + diffuse + specular, 1.0);
    }

    vTexCoord = texCoord;
}  


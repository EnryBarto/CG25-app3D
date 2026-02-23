#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec3 vertexNormal;  // normal attribute 2
layout(location = 3) in vec2 texCoord; // texture attribute
#define MAX_LIGHTS 10

out vec4 ourColor; // output a color to the fragment shader
out vec2 vTexCoord;
uniform mat4 Projection;  // Uniform variable: stays the same for every vertex of the primitive and is set from outside
uniform mat4 Model;
uniform mat4 View;
uniform vec3 ViewPos;

// Structure for handling a point light
struct PointLight {
	vec3 position;
	vec3 color;
	float power;
};

// Definition of a uniform variable using the PointLight structure
uniform PointLight lights[MAX_LIGHTS];
uniform int numLights;

// Structure for handling a material

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Uniform variable
uniform Material material;

float strenght = 0.1;
void main() {
    // Transform vertices from object space (aPos) to clip space by applying Model, View and Projection
    // (Resulting coordinates are in normalized device coordinates, range -1..1)
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);

    // Transform the vertex coordinates (aPos) into view space
    vec4 eyePosition = View * Model * vec4(aPos, 1.0);

    vec3 totalLight = vec3(0);

    for (int i = 0; i < numLights; i++) {
        // Transform the light position into view space
        vec4 eyeLightPos = View * vec4(lights[i].position, 1.0);

        // Transform the vertex normal into view space
        vec3 N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);

        // Compute the light direction L, reflection direction R and view direction V
        vec3 V = normalize(ViewPos - eyePosition.xyz);
        vec3 L = normalize((eyeLightPos - eyePosition).xyz);
        vec3 R = reflect(-L, N);  //Costruisce la direzione riflessa di L rispesso alla normale

        // Ambient
        vec3 ambient = strenght * lights[i].power * material.ambient;

        // Diffuse
        float coseno_angolo_theta = max(dot(L, N), 0);
        vec3 diffuse = lights[i].power * lights[i].color * coseno_angolo_theta * material.diffuse;

        // Specular
        float coseno_angolo_alfa = pow(max(dot(V, R), 0), material.shininess);
        vec3 specular = lights[i].power * lights[i].color * coseno_angolo_alfa * material.specular;

        // Total contribution
        totalLight += ambient + diffuse + specular;
    }

    ourColor = vec4(totalLight, 1.0);

    vTexCoord = texCoord;  
}  


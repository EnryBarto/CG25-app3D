#version 330 core
#define MAX_LIGHTS 10
in vec3 N, L[MAX_LIGHTS], R[MAX_LIGHTS], V[MAX_LIGHTS];
in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform bool uUseTexture;

//Struttura per la gestione di un punto luce
struct PointLight {
    vec3 position;
    vec3 color;
    float power;
};

//definizione di una variabile uniform che ha la struttura PointLight
uniform PointLight lights[MAX_LIGHTS];
uniform int numLights;

//Struttura per la gestione di un materiale

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

//Variabile uniforme
uniform Material material;
out vec4 FragColor;  

float strenght = 0.1;

void main() {

    FragColor = vec4(0, 0, 0, 1);

    for (int i = 0; i < numLights; i++) {

        //ambientale
        vec3 ambient = strenght * lights[i].power * material.ambient;

        //diffuse
        float coseno_angolo_theta = max(dot(L[i], N), 0);

        vec3 diffuse = lights[i].power * lights[i].color * coseno_angolo_theta * material.diffuse;

        //speculare
        float coseno_angolo_alfa = pow(max(dot(V[i], R[i]), 0), material.shininess);

        vec3 specular = lights[i].power * lights[i].color * coseno_angolo_alfa * material.specular;

        vec4 baseColor = vec4(ambient + diffuse + specular, 1.0);

        FragColor += baseColor;
    }

}
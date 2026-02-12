#version 330 core

in vec3 N, L, R, V;
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
uniform PointLight light;

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
void main()
{
    //ambientale
    vec3 ambient = strenght * light.power * material.ambient;

    //diffuse
    float coseno_angolo_theta = max(dot(L, N), 0);

    vec3 diffuse = light.power * light.color * coseno_angolo_theta * material.diffuse;

    //speculare
    float coseno_angolo_alfa = pow(max(dot(V, R), 0), material.shininess);

    vec3 specular = light.power * light.color * coseno_angolo_alfa * material.specular;

     vec4 baseColor = vec4(ambient + diffuse + specular, 1.0);

    
     
    FragColor = baseColor;
}
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <assimp/types.h>
#include <assimp/material.h>

using namespace glm;
using namespace std;

class Material {
	public:
        Material(string name, vec3 ambient, vec3 diffuse, vec3 specular, float shininess);
        Material(const aiMaterial* loadedMaterial);
        string getName();
        vec3 getAmbient();
        vec3 getDiffuse();
        vec3 getSpecular();
        float getShininess();
        void updateValues(vec3 ambient, vec3 diffuse, vec3 specular, float shininess);

    private:
        string name;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shininess;
};
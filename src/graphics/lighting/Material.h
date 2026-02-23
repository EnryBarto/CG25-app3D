#pragma once
#include <glm/ext/vector_float3.hpp>
#include <string>
#include <assimp/material.h>
#include <assimp/types.h>
#include <iostream>

using namespace std;
using namespace glm;

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
#include "Material.h"

#include <iostream>
#include <stdexcept>

Material::Material(string name, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
	this->name = name;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

Material::Material(const aiMaterial* loadedMaterial) {

	if (!loadedMaterial) throw std::runtime_error("loadedMaterial is null");

	this->name = loadedMaterial->GetName().C_Str();

	aiColor3D color;

	if (loadedMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color) == aiReturn_SUCCESS) {
		this->ambient = glm::vec3(color.r, color.g, color.b);
	} else {
		std::cerr << "Error loading ambient component for " << this->name << std::endl;
		this->ambient = glm::vec3(0.1f);
	}

	if (loadedMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == aiReturn_SUCCESS) {
		this->diffuse = glm::vec3(color.r, color.g, color.b);
	} else {
		std::cerr << "Error loading diffuse component for " << this->name << std::endl;
		this->diffuse = glm::vec3(1.0f, 0.2f, 0.1f);
	}

	if (loadedMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == aiReturn_SUCCESS) {
		this->specular = glm::vec3(color.r, color.g, color.b);
	} else {
		std::cerr << "Error loading specular component for " << this->name << std::endl;
		this->specular = glm::vec3(0.5f);
	}
	
	float value;

	if (loadedMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, value) == aiReturn_SUCCESS) {
		this->shininess = value;
	} else {
		std::cerr << "Error loading shininess component for " << this->name << std::endl;
		this->shininess = 50;
	}
}

string Material::getName() {
	return this->name;
}

vec3 Material::getAmbient() {
	return this->ambient;
}

vec3 Material::getDiffuse() {
	return this->diffuse;
}

vec3 Material::getSpecular() {
	return this->specular;
}

float Material::getShininess() {
	return this->shininess;
}

void Material::updateValues(vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

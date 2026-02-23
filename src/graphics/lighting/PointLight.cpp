#include "PointLight.h"
#include "../renderable/MeshGeometryFactory.h"

PointLight::PointLight(Shader* shader): PointLight(vec3(0, 10, 0), vec3(1), 15, shader) {
}

PointLight::PointLight(vec3 position, vec3 color, float power, Shader* shader) {
	this->gpuBuffer = new RenderablePointLight();
	MeshGeometry* sphere = MeshGeometryFactory::createSphere(vec4(1));
	this->gpuBuffer->initVao(sphere);
	this->gpuBuffer->setShader(shader);
	delete sphere;
	this->setPosition(position);
	this->setColor(color);
	this->setPower(power);
}

PointLight::~PointLight() {
	delete this->gpuBuffer;
}

vec3 PointLight::getPosition() {
	return this->position;
}

vec3 PointLight::getColor() {
	return this->color;
}

float PointLight::getPower() {
	return this->power;
}

void PointLight::setPosition(vec3 newPos) {
	this->position = newPos;
	this->modelMatrix = scale(translate(mat4(1), this->position), vec3(0.5f));
}

void PointLight::setColor(vec3 newColor) {
	this->color = newColor;
	this->updateSphereColor();
}

void PointLight::setPower(float power) {
	this->power = power >= 0 ? power : 1;
	this->updateSphereColor();
}

void PointLight::render(const mat4& viewMatrix, const mat4& projectionMatrix) {
	this->gpuBuffer->render(modelMatrix, viewMatrix, projectionMatrix);
}

void PointLight::updateSphereColor() {
	this->gpuBuffer->updateColor(this->color * pow((this->power - MIN_LIGHT_POWER) / (MAX_LIGHT_POWER - MIN_LIGHT_POWER), 0.3f));
}

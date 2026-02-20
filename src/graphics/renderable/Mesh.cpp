#include "Mesh.h"

Mesh::Mesh(MeshGeometry* geometry, Shader* basicShader, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
	this->geometry = geometry;
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(geometry);
	this->gpuObject->setShader(basicShader);
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scaleVector;
	this->computeModelMatrix();
}

void Mesh::computeModelMatrix() {
	this->modelMatrix = translate(mat4(1.0), this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) this->modelMatrix = rotate(this->modelMatrix, radians(this->angle), this->rotationAxis);
	this->modelMatrix = scale(this->modelMatrix, this->scaleVector);
}

void Mesh::render(const mat4& globalModelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor) {
	mat4 modelMatrix = globalModelMatrix * this->modelMatrix; // Apply first the local transform, next the global
	this->gpuObject->render(modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor);
}
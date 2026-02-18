#include "Mesh.h"

Mesh::Mesh(MeshGeometry* geometry, Shader* basicShader, vec3 translation, vec3 rotationAxis, float angle, vec3 scale) {
	this->geometry = geometry;
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(geometry);
	this->gpuObject->setShader(basicShader);
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scale;
}

mat4 Mesh::getModelMatrix() {
	mat4 m = mat4(1.0);
	m = translate(m, this->translation);
	if (this->angle != 0) m = rotate(m, radians(this->angle), this->rotationAxis);
	m = scale(m, this->scaleVector);
	return m;
}

void Mesh::render(mat4* globalModelMatrix, mat4* viewMatrix, mat4* projectionMatrix, vec3* camPos) {
	mat4 localModel = this->getModelMatrix();
	mat4 modelMatrix = *globalModelMatrix * localModel;
	this->gpuObject->render(&modelMatrix, viewMatrix, projectionMatrix, camPos);
}
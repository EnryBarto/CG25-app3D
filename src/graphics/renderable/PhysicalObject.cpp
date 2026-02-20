#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scaleVector;
	this->computeModelMatrix();
}

void PhysicalObject::addMesh(Mesh* toAdd) {
	this->meshes.push_back(toAdd);
}

void PhysicalObject::computeModelMatrix() {
	this->modelMatrix = translate(mat4(1.0), this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) this->modelMatrix = rotate(this->modelMatrix, radians(this->angle), this->rotationAxis);
	this->modelMatrix = scale(this->modelMatrix, this->scaleVector);
}

void PhysicalObject::render(const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor) {
	for (Mesh* m : this->meshes) {
		m->render(this->modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor);
	}
}
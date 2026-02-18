#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(vec3 translation, vec3 rotationAxis, float angle, vec3 scale) {
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scale;
}

void PhysicalObject::addMesh(Mesh* toAdd) {
	this->meshes.push_back(toAdd);
}

void PhysicalObject::render(mat4* viewMatrix, mat4* projectionMatrix, vec3* camPos) {
	mat4 modelMatrix = this->getModelMatrix();
	for (Mesh* m : this->meshes) {
		m->render(&modelMatrix, viewMatrix, projectionMatrix, camPos);
	}
}

mat4 PhysicalObject::getModelMatrix() {
	mat4 m = mat4(1.0);
	m = translate(m, this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) m = rotate(m, radians(this->angle), this->rotationAxis);
	m = scale(m, this->scaleVector);
	return m;
}
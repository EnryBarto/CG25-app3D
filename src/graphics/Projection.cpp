#include "Projection.h"

Projection::Projection(float aspectRatio, float _fov) {
	this->fovY = _fov;
	this->nearPlane = PROJ_NEARPLANE;
	this->farPlane = PROJ_FARPLANE;
	this->changeAspectRatio(aspectRatio);
}

void Projection::changeAspectRatio(float newAspectRatio) {
	this->aspectRatio = newAspectRatio;
	this->computeProjectionMatrix();
}

void Projection::changeFov(float newFov) {
	this->fovY = newFov;
	this->computeProjectionMatrix();
}

const mat4& Projection::getProjectionMatrix() {
	return this->matrix;
}

void Projection::computeProjectionMatrix() {
	this->matrix = perspective(radians(this->fovY), this->aspectRatio, this->nearPlane, this->farPlane);
}

#include "Projection.h"

Projection::Projection(int width, int height) {
	this->fovY = PROJ_FOVY;
	this->nearPlane = PROJ_NEARPLANE;
	this->farPlane = PROJ_FARPLANE;
	this->changeAspectRatio((float)width / (float)height);
}

void Projection::changeAspectRatio(float newAspectRatio) {
	this->aspectRatio = newAspectRatio;
	this->computeProjectionMatrix();
}

const mat4& Projection::getProjectionMatrix() {
	return this->matrix;
}

void Projection::computeProjectionMatrix() {
	this->matrix = perspective(radians(this->fovY), this->aspectRatio, this->nearPlane, this->farPlane);
}

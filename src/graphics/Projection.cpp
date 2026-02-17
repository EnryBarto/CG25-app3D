#include "Projection.h"

Projection::Projection(int width, int height) {
	this->fovY = PROJ_FOVY;
	this->aspectRatio = (GLfloat)width / (GLfloat)height;
	this->nearPlane = PROJ_NEARPLANE;
	this->farPlane = PROJ_FARPLANE;
	this->matrix = perspective(radians(this->fovY), this->aspectRatio, this->nearPlane, this->farPlane);
}

mat4 Projection::getMatrix() {
	return mat4(this->matrix);
}

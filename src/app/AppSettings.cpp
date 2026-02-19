#include "AppSettings.h"

bool AppSettings::isWireframeActive() {
	return this->_wireframeActive;
}

bool AppSettings::isWireframeActiveChanged() {
	return this->_wireframeActiveChanged;
}

bool AppSettings::isPaused() {
	return this->_pause;
}

bool AppSettings::isShowingCommands() {
	return this->_showingCommands;
}

float AppSettings::getCurrentFov() {
	this->_fovChanged = false;
	return this->_fov;
}

bool AppSettings::isFovChanged() {
	return this->_fovChanged;
}

float AppSettings::getCurrentCameraSpeed() {
	this->_cameraSpeedChanged = false;
	return this->_cameraSpeed;
}

bool AppSettings::isCameraSpeedChanged() {
	return this->_cameraSpeedChanged;
}

float AppSettings::getCurrentMouseSensitivity() {
	return this->_mouseSensitivity;
}

void AppSettings::toggleWireframe() {
	this->_wireframeActiveChanged = true;
	this->_wireframeActive = !this->_wireframeActive;
}

void AppSettings::setWireframeUnchanged() {
	this->_wireframeActiveChanged = false;
}

void AppSettings::togglePause() {
	this->_pause = !this->_pause;
}

void AppSettings::toggleShowingCommands() {
	this->_showingCommands = !this->_showingCommands;
}

void AppSettings::setFov(float newFov) {
	if (newFov == this->_fov) return;
	this->_fov = glm::clamp(newFov, PROJ_FOVY_MIN, PROJ_FOVY_MAX);
	this->_fovChanged = true;
}

void AppSettings::setCameraSpeed(float newCameraSpeed) {
	if (newCameraSpeed == this->_cameraSpeed) return;
	this->_cameraSpeed = glm::clamp(newCameraSpeed, CAMERA_SPEED_MIN, CAMERA_SPEED_MAX);
	this->_cameraSpeedChanged = true;
}

void AppSettings::setMouseSensitivity(float newMouseSensitivity) {
	if (newMouseSensitivity == this->_mouseSensitivity) return;
	this->_mouseSensitivity = glm::clamp(newMouseSensitivity, MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX);
}

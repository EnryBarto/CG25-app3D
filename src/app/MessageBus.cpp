#include "MessageBus.h"

void MessageBus::aspectRatioChanged(float newAspectRatio) {
	this->_aspectRatioChanged = true;
	this->newAspectRatio = newAspectRatio;
}

bool MessageBus::isAspectRatioChanged() {
	return this->_aspectRatioChanged;
}

float MessageBus::getNewAspectRatio() {
	float toReturn = this->newAspectRatio;
	this->_aspectRatioChanged = false;
	return toReturn;
}

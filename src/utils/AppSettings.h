#pragma once

#include "../utils/constants.h"

class AppSettings {

	public:
		bool isWireframeActive();
		bool isWireframeActiveChanged();
		bool isShowingCommands();
		float getCurrentFov();
		bool isFovChanged();
		float getCurrentCameraSpeed();
		bool isCameraSpeedChanged();
		float getCurrentTrackballSpeed();
		float getCurrentMouseSensitivity();
		bool isAnchorActive();
		bool isBoundingBoxActive();

		void toggleWireframe();
		void setWireframeUnchanged();
		void toggleShowingCommands();
		void setFov(float newFov);
		void setCameraSpeed(float newCameraSpeed);
		void setTrackballSpeed(float newTrackballSpeed);
		void setMouseSensitivity(float newMouseSensitivity);
		void toggleAnchor();
		void toggleBoundingBox();

	private:
		bool _wireframeActive = false;
		bool _wireframeActiveChanged = false;
		bool _showingCommands = false;
		float _fov = PROJ_FOVY_DEFAULT;
		bool _fovChanged = false;
		float _cameraSpeed = CAMERA_SPEED_DEFAULT;
		bool _cameraSpeedChanged = false;
		float _mouseSensitivity = MOUSE_SENSITIVITY_DEFAULT;
		bool _anchor = false;
		bool _boundingBox = false;
		float _trackballSpeed = TRACKBALL_SPEED_DEFAULT;
};
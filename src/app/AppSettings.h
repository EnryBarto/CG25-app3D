#pragma once
#include "../settings.h"
#include <glm/common.hpp>

class AppSettings {

	public:
		bool isWireframeActive();
		bool isWireframeActiveChanged();
		bool isPaused();
		bool isShowingCommands();
		float getCurrentFov();
		bool isFovChanged();
		float getCurrentCameraSpeed();
		bool isCameraSpeedChanged();
		float getCurrentMouseSensitivity();

		void toggleWireframe();
		void setWireframeUnchanged();
		void togglePause();
		void toggleShowingCommands();
		void setFov(float newFov);
		void setCameraSpeed(float newCameraSpeed);
		void setMouseSensitivity(float newMouseSensitivity);

	private:
		bool _wireframeActive = false;
		bool _wireframeActiveChanged = false;
		bool _pause = false;
		bool _showingCommands = false;
		float _fov = PROJ_FOVY_DEFAULT;
		bool _fovChanged = false;
		float _cameraSpeed = CAMERA_SPEED_DEFAULT;
		bool _cameraSpeedChanged = false;
		float _mouseSensitivity = MOUSE_SENSITIVITY_DEFAULT;
};
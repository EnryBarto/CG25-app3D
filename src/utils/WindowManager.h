#pragma once

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "constants.h"

using namespace glm;

class WindowManager {
	public:
		WindowManager();
		GLFWwindow* getWindow();
		void frameBufferChanged();
		bool isFrameBufferChanged();
		bool isFullScreen();
		bool isVsyncActive();
		float getAspectRatio();
		void toggleFullScreen();
		void toggleVsync();
		vec2 getCurrentResolution();

	private:
		GLFWwindow* window;
		bool _fullScreen, _frameBufferChanged, _vSync = VSYNC_ENABLED;
		int lastWindowPosition[2], lastWindowSize[2];

		GLFWmonitor* getCurrentMonitor();
};
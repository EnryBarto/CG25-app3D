#pragma once

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class WindowManager {
	public:
		WindowManager();
		GLFWwindow* getWindow();
		void frameBufferChanged();
		bool isFrameBufferChanged();
		bool isFullScreen();
		float getAspectRatio();
		void toggleFullScreen();
		vec2 getCurrentResolution();

	private:
		GLFWwindow* window;
		bool _fullScreen, _frameBufferChanged;
		int lastWindowPosition[2], lastWindowSize[2];

		GLFWmonitor* getCurrentMonitor();
};
#pragma once

#include "../libs.h"
#include "../app/initializations.h"

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
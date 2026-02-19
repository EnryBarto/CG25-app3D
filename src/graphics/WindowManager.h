#pragma once

#include "../libs.h"
#include "../app/initializations.h"

class WindowManager {
	public:
		WindowManager();
		GLFWwindow* getWindow();
		void frameBufferChanged();
		bool isFrameBufferChanged();
		float getAspectRatio();
		void toggleFullScreen();


	private:
		GLFWwindow* window;
		bool _fullScreen, _frameBufferChanged;
		int lastWindowPosition[2], lastWindowSize[2];

		GLFWmonitor* getCurrentMonitor();
};
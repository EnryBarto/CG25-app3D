#include "callbacks.h"

extern WindowManager* windowManager;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) return;

	switch (key) {
		case GLFW_KEY_F11:
			windowManager->toggleFullScreen();
			break;
	}
}

void cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn) {

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	windowManager->frameBufferChanged();
}
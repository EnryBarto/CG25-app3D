#include "callbacks.h"

extern MessageBus* messageBus;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn) {

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	// We want to use the full screen but mantaining the proportions
	messageBus->aspectRatioChanged((float)newWidth / (float)newHeight);
	glViewport(0, 0, newWidth, newHeight);
}
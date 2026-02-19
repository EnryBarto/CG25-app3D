#include "callbacks.h"

extern WindowManager* windowManager;
extern Camera* camera;
extern bool showingCommands;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) return;

	switch (key) {
        case GLFW_KEY_F1:
            showingCommands = !showingCommands;
            break;

		case GLFW_KEY_F11:
			windowManager->toggleFullScreen();
			break;

        // Move the cursor outside the window
        case GLFW_KEY_ESCAPE:
            if (windowManager->isFullScreen()) windowManager->toggleFullScreen();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(window, (int)-150, (int)-150);
            break;
	}
}

void cursor_position_callback(GLFWwindow* window, double xPosIn, double yPosIn) {

    // When the mouse is captured, hide it
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    yPosIn = height - yPosIn; // Inverts the zero of the y-axis

    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    // Because the pointer is in the center of the screen, the movement is the distance between the center and the position of the mouse 
    float xOffset = ((float)xPosIn - centerX) * MOUSE_SENSITIVITY;
    float yOffset = ((float)yPosIn - centerY) * MOUSE_SENSITIVITY;

    // The movement of the mouse along the x axis, causes the rotation around the y axis and vice versa
    camera->changeDirection(yOffset, xOffset);

    // Set the cursor at the center of the screen
    glfwSetCursorPos(window, (int)centerX, (int)centerY);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	windowManager->frameBufferChanged();
}

#include "callbacks.h"

#include "../App.h"

extern App app;
int lastMousePosX = 0, lastMousePosY = 0;

// Utility function
vec3 cursor_to_unit_sphere(GLFWwindow* window, int x, int y);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) return;

	switch (key) {
        case GLFW_KEY_F1:
            app.getAppSettings()->toggleShowingCommands();
            break;

		case GLFW_KEY_F11:
			app.getWindowManager()->toggleFullScreen();
			break;

        case GLFW_KEY_ESCAPE:
            app.escPressed();
            break;

        case GLFW_KEY_P:
            app.togglePause();
            break;

        case GLFW_KEY_O:
            app.toggleObjectList();
            break;

        case GLFW_KEY_SPACE:
            app.toggleMode();
            break;

        case GLFW_KEY_L:
            app.toggleLightSettings();
            break;

        case GLFW_KEY_UP:
            app.getScene()->getCamera()->changeDirection(app.getAppSettings()->getCurrentCameraSpeed() * ARROW_KEY_CAMERA_SPEED_FACTOR, 0);
            break;

        case GLFW_KEY_DOWN:
            app.getScene()->getCamera()->changeDirection(-app.getAppSettings()->getCurrentCameraSpeed() * ARROW_KEY_CAMERA_SPEED_FACTOR, 0);
            break;

        case GLFW_KEY_RIGHT:
            app.getScene()->getCamera()->changeDirection(0, app.getAppSettings()->getCurrentCameraSpeed() * ARROW_KEY_CAMERA_SPEED_FACTOR);
            break;

        case GLFW_KEY_LEFT:
            app.getScene()->getCamera()->changeDirection(0, -app.getAppSettings()->getCurrentCameraSpeed() * ARROW_KEY_CAMERA_SPEED_FACTOR);
            break;
	}
}

void cursor_position_callback(GLFWwindow* window, double currentMousePosX, double currentMousePosY) {
    
    switch (app.getCurrentAppState()) {

        case AppState::NAVIGATION: {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            currentMousePosY = height - currentMousePosY; // Inverts the zero of the y-axis

            vec2 center = vec2(width, height) / 2.0f;

            // Because the pointer is in the center of the screen, the movement is the distance between the center and the position of the mouse
            vec2 offset = (vec2(currentMousePosX, currentMousePosY) - center) * app.getAppSettings()->getCurrentMouseSensitivity();

            // The movement of the mouse along the x axis, causes the rotation around the y axis and vice versa
            app.getScene()->getCamera()->changeDirection(offset.y, offset.x);

            // Set the cursor at the center of the screen
            glfwSetCursorPos(window, (int)center.x, (int)center.y);
        }break;

        case AppState::MOVING_TRACKBALL: {
            // Get the two positions on the unit sphere
            vec3 destination = cursor_to_unit_sphere(window, (int)currentMousePosX, (int)currentMousePosY);
            vec3 origin = cursor_to_unit_sphere(window, lastMousePosX, lastMousePosY);

            // Calculate the vector joining the two points
            vec3 difference = destination - origin;

            if (difference != vec3(0)) {
                // Aproximate the rotation angle with ||destination - origin||
                float angle = glm::length(difference) * app.getAppSettings()->getCurrentTrackballSpeed();

                // The rotation axis is perpendicular to the origin and destination vector, so the cross product is used
                vec3 rotationAxis = glm::cross(origin, destination);

                // Rotate the camera and undo the operation if there was a collision
                app.getScene()->getCamera()->rotateAroundCameraTarget(rotationAxis, angle);
                if (app.getScene()->isCameraColliding()) app.getScene()->getCamera()->undoLastOperation();
            }

            lastMousePosX = (int)currentMousePosX;
            lastMousePosY = (int)currentMousePosY;
            } break;
            
        default:
            break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    // Retrieve mouse position
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    switch (app.getCurrentAppState()) {
        case AppState::PICKING:
            if (action == GLFW_PRESS) {
                app.pick(vec2(xPos, yPos));
            }
            break;
        case AppState::TRACKBALL:
            if (action == GLFW_PRESS) {
                lastMousePosX = (int)xPos;
                lastMousePosY = (int)yPos;
                app.toggleMovingTrackball();
            }
            break;
        case AppState::MOVING_TRACKBALL:
            if (action == GLFW_RELEASE) {
                app.toggleMovingTrackball();
            }
            break;
    }            
}

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	app.getWindowManager()->frameBufferChanged();
}

void dragdrop_callback(GLFWwindow* window, int path_count, const char* paths[]) {
    app.loadObjectsFromFile(paths, path_count);
}

// Mapping the mouse click to the projected point on the hemisphere with center the origin and radius
vec3 cursor_to_unit_sphere(GLFWwindow* window, int x, int y) {

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Map to [-1;1]
    vec3 point;

    point.x = (2.0f * x - width) / width;
    point.y = (height - 2.0f * y) / height;

    float tmp = glm::dot(vec2(point), vec2(point)); // Square of the distance of the projected point from the center in the XY plane (radius^2)
    float delta = 1.0f - tmp; // Amount missing from r^2 to reach 1

    if (delta > 0.0f) {
        point.z = sqrt(delta);
    } else {
        // The click is outside the semisphere: there's no z that makes  x^2 + y^2 + z^2 = 1
        point.z = 0;
    }

    return normalize(point);
}
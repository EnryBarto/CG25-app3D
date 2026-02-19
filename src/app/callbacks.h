#ifndef __CALLBACKS_H
#define __CALLBACKS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../graphics/WindowManager.h"
#include "../graphics/Camera.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight);

#endif
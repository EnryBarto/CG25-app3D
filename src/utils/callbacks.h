#pragma once

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App; // Forward declaration

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double currentMousePosX, double currentMousePosY);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight);
void dragdrop_callback(GLFWwindow* window, int path_count, const char* paths[]);
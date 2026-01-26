#ifndef __INITIALIZATIONS_H
#define __INITIALIZATIONS_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "settings.h"
#include "callbacks.h"

GLFWwindow* initialize_all();
int init_gl_glfw();
GLFWwindow* init_window_context_events();
void init_callbacks(GLFWwindow* window);
void init_imgui(GLFWwindow* window);

#endif
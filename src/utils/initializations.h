#ifndef __INITIALIZATIONS_H
#define __INITIALIZATIONS_H

#define GLFW_INCLUDE_NONE // Prevent GLFW from including the default system OpenGL headers to avoid symbol redefinition conflicts with the GLAD loader
#define IMGUI_IMPL_OPENGL_LOADER_GLAD // Instruct Dear ImGui's OpenGL backend to use GLAD as the function pointer loader for rendering commands

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <iostream>
#include <string>
#include <map>

#include "constants.h"
#include "callbacks.h"
#include "../shader/Shader.h"
#include "../lighting/Material.h"
#include "../texture/Texture.h"
#include "../scene/Scene.h"

using namespace std;

int init_gl_glfw();
GLFWwindow* init_window_context_events();
void init_callbacks(GLFWwindow* window);
void init_imgui(GLFWwindow* window);
map<string, Shader*>* init_shaders();
map<string, Texture*>* init_textures();
map<string, Material*>* init_materials();
void add_scene_objects(Scene* scene, map<string, Shader*>* shaders, map<string, Texture*>* textures, map<string, Material*>* materials);

#endif
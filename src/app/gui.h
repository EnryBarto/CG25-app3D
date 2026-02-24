#ifndef __GUI_H
#define __GUI_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include "../graphics/renderable/PhysicalObject.h"

void show_commands();
void show_settings();
void show_status_bar();
ImVec2 show_object_inspector();
void show_mesh_inspector();
void show_objects_list();
void close_gui();
void show_start_file_loading(const char* path);
void show_file_error(const char* path, const char* error);
void show_mesh_file_uploaded(const char* path, PhysicalObject* uploadedObject, char* nameBuffer);
void show_texture_file_uploaded(const char* path, Texture* uploadedTexture, char* nameBuffer);
void show_light_settings();

#endif
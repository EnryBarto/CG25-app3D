#ifndef __GUI_H
#define __GUI_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

void show_commands();
void show_settings();
void show_status_bar();
ImVec2 show_object_inspector();
void show_mesh_inspector();
void close_gui();

#endif
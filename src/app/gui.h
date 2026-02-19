#ifndef __GUI_H
#define __GUI_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include "AppSettings.h"

void show_commands();
void show_settings();
void close_gui();

#endif
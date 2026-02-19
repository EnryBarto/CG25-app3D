#include "gui.h"

void show_commands() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);

    ImGui::Begin("Commands", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("----- CAMERA COMMANDS -----");
    ImGui::Text("W: Move forward");
    ImGui::Text("A: Move left");
    ImGui::Text("S: Move backward");
    ImGui::Text("D: Move right");
    ImGui::Text("U: Move up");
    ImGui::Text("Y: Move down");
    ImGui::NewLine();
    ImGui::Text("----- WINDOW COMMANDS -----");
    ImGui::Text("F1: Toggle commands window");
    ImGui::Text("F11: Toggle fullscreen mode");
    ImGui::Text("ESC: Detach mouse from window and exit fullscreen");
    ImGui::NewLine();

    ImGui::End();
}

void close_gui() {
    ImGui_ImplOpenGL3_Shutdown();   // Shut down the OpenGL integration
    ImGui_ImplGlfw_Shutdown();      // Shut down the GLFW integration
    ImGui::DestroyContext();        // Destroy the ImGui context
}
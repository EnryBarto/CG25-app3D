#include "gui.h"

extern AppSettings* currentSettings;

void show_commands() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

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
    ImGui::Text("ESC: Toggle pause and open / close settings");
    ImGui::NewLine();

    ImGui::End();
}

void show_settings() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);

    ImGui::Begin("PAUSE - Settings", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    bool isActive = currentSettings->isWireframeActive();
    if (ImGui::Checkbox("Wireframe", &isActive)) currentSettings->toggleWireframe();

    bool anchor = currentSettings->isAnchorActive();
    if (ImGui::Checkbox("Anchor", &anchor)) currentSettings->toggleAnchor();

    float tempFov = currentSettings->getCurrentFov();
    if (ImGui::SliderFloat(" FOV", &tempFov, PROJ_FOVY_MIN, PROJ_FOVY_MAX)) currentSettings->setFov(tempFov);

    float tempCameraSpeed = currentSettings->getCurrentCameraSpeed();
    if (ImGui::SliderFloat(" Camera Speed", &tempCameraSpeed, CAMERA_SPEED_MIN, CAMERA_SPEED_MAX)) currentSettings->setCameraSpeed(tempCameraSpeed);

    float tempMouseSensitivity = currentSettings->getCurrentMouseSensitivity();
    if (ImGui::SliderFloat(" Mouse Sensitivity", &tempMouseSensitivity, MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX)) currentSettings->setMouseSensitivity(tempMouseSensitivity);

    ImGui::NewLine();
    if (ImGui::Button("Resume")) currentSettings->togglePause();
    if (ImGui::Button("Quit")) currentSettings->exit();
    ImGui::NewLine();

    ImGui::End();
}

void close_gui() {
    ImGui_ImplOpenGL3_Shutdown();   // Shut down the OpenGL integration
    ImGui_ImplGlfw_Shutdown();      // Shut down the GLFW integration
    ImGui::DestroyContext();        // Destroy the ImGui context
}
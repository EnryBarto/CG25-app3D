#include "gui.h"

#include "App.h"

extern App app;

void show_commands() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

    ImGui::Begin("Commands", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("----- COMMANDS -----");
    ImGui::Text("Space bar: Toggle Picking / Navigation modes");
    ImGui::NewLine();
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

    bool isActive = app.getAppSettings()->isWireframeActive();
    if (ImGui::Checkbox("Wireframe", &isActive)) app.getAppSettings()->toggleWireframe();

    bool anchor = app.getAppSettings()->isAnchorActive();
    if (ImGui::Checkbox("Anchor", &anchor)) app.getAppSettings()->toggleAnchor();

    float tempFov = app.getAppSettings()->getCurrentFov();
    if (ImGui::SliderFloat(" FOV", &tempFov, PROJ_FOVY_MIN, PROJ_FOVY_MAX)) app.getAppSettings()->setFov(tempFov);

    float tempCameraSpeed = app.getAppSettings()->getCurrentCameraSpeed();
    if (ImGui::SliderFloat(" Camera Speed", &tempCameraSpeed, CAMERA_SPEED_MIN, CAMERA_SPEED_MAX)) app.getAppSettings()->setCameraSpeed(tempCameraSpeed);

    float tempMouseSensitivity = app.getAppSettings()->getCurrentMouseSensitivity();
    if (ImGui::SliderFloat(" Mouse Sensitivity", &tempMouseSensitivity, MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX)) app.getAppSettings()->setMouseSensitivity(tempMouseSensitivity);

    ImGui::NewLine();
    if (ImGui::Button("Resume")) app.togglePause();
    if (ImGui::Button("Quit")) app.close();
    ImGui::NewLine();

    ImGui::End();
}

void show_status_bar() {

    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - STATUS_BAR_PADDING * 2, 0.0f));
    ImGui::SetNextWindowPos(
        ImVec2(STATUS_BAR_PADDING, app.getWindowManager()->getCurrentResolution().y - STATUS_BAR_PADDING),
        ImGuiCond_Always,
        ImVec2(0.0f, 1.0f) // Consider as Y pivot the end of the window
    );

    ImGui::Begin("Status", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoMove
    );
    vec3 cameraPos = app.getScene()->getCamera()->getPosition();
    ImGui::Text("Position: (%.1f, %.1f, %.1f) - Status: %s - FPS: %.1f",
        cameraPos.x, cameraPos.y, cameraPos.z,
        appStateToString(app.getCurrentAppState()),
        ImGui::GetIO().Framerate);
    ImGui::End();
}

void close_gui() {
    ImGui_ImplOpenGL3_Shutdown();   // Shut down the OpenGL integration
    ImGui_ImplGlfw_Shutdown();      // Shut down the GLFW integration
    ImGui::DestroyContext();        // Destroy the ImGui context
}
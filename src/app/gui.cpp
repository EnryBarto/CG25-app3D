#include "gui.h"

#include "App.h"

extern App app;

void show_commands() {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_FirstUseEver);

    ImGui::Begin("Commands", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("----- COMMANDS -----");
    ImGui::Text("Space bar: Toggle Picking / Navigation modes");
    ImGui::Text("ESC: Go back to previous mode");
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
    ImGui::Text("P: Toggle pause and open / close settings");
    ImGui::NewLine();

    ImGui::End();
}

void show_settings() {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

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
    ImGui::Text("Press F1 to show the helper"); 
    ImGui::NewLine();
    if (ImGui::Button("Resume")) app.togglePause();
    if (ImGui::Button("Quit")) app.close();
    ImGui::NewLine();

    ImGui::End();
}

void show_status_bar() {

    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));
    ImGui::SetNextWindowPos(
        ImVec2(GUI_WINDOWS_PADDING, app.getWindowManager()->getCurrentResolution().y - GUI_WINDOWS_PADDING),
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

ImVec2 show_object_inspector() {

    if (app.getScene()->getSelectedObject() == nullptr) return ImVec2(0, 0);

    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("OBJECT INSPECTOR", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Name: %s", app.getScene()->getSelectedObject()->getName());
    ImGui::Text("                        "); // Sets the min width of the window

    ImGui::Text("Meshes:");

    PhysicalObject* selectedObject = app.getScene()->getSelectedObject();

    for (auto m : *selectedObject->getMeshes()) {
        if (ImGui::Button((m.first + " ->").c_str())) app.setSelectedMesh(selectedObject, m.first);
    }

    ImGui::NewLine();
    if (ImGui::Button("Close")) app.resetObjectSelection();
    ImGui::NewLine();
    
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::End();

    return windowSize;
}

void show_mesh_inspector() {

    ImVec2 objectInspectorSize = show_object_inspector();

    if (get<1>(app.getScene()->getSelectedMesh()) == nullptr) return;

    ImGui::SetNextWindowPos(ImVec2(objectInspectorSize.x + 2 * GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("MESH INSPECTOR", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Mesh name: %s", get<0>(app.getScene()->getSelectedMesh()));
    ImGui::Text("                        "); // Sets the min width of the window
    
    ImGui::NewLine();
    if (ImGui::Button("Close")) app.resetMeshSelection();
    ImGui::NewLine();
    
    ImGui::End();
}

void close_gui() {
    ImGui_ImplOpenGL3_Shutdown();   // Shut down the OpenGL integration
    ImGui_ImplGlfw_Shutdown();      // Shut down the GLFW integration
    ImGui::DestroyContext();        // Destroy the ImGui context
}
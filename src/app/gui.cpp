#include "gui.h"

#include "App.h"

extern App app;

void show_commands() {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_FirstUseEver);

    ImGui::Begin("Commands", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("----- COMMANDS -----");
    ImGui::Text("Space bar: Toggle Picking / Navigation modes");
    ImGui::Text("ESC: Go back to previous mode");
    ImGui::Text("Drag & Drop: Upload obj file");
    ImGui::NewLine();
    ImGui::Text("----- CAMERA COMMANDS -----");
    ImGui::Text("W: Move forward");
    ImGui::Text("A: Move left");
    ImGui::Text("S: Move backward");
    ImGui::Text("D: Move right");
    ImGui::Text("U: Move up");
    ImGui::Text("Y: Move down");
    ImGui::Text("Arrows: Rotate camera");
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

    PhysicalObject* selectedObj = app.getScene()->getSelectedObject();
    
    if (selectedObj == nullptr) return ImVec2(0, 0);

    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("OBJECT INSPECTOR", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Selected object:");
    ImGui::TextWrapped(selectedObj->getName().c_str());
    ImGui::NewLine();

    vec3 translation = selectedObj->getTranslationVector();
    vec3 rotationAxis = selectedObj->getRotationAxis();
    float rotationAngle = selectedObj->getRotationAngle();
    vec3 scaleVector = selectedObj->getScaleVector();

    ImGui::Text("Edit model matrix:");
    bool changed = false;

    changed |= ImGui::DragFloat3(" Position", glm::value_ptr(translation), 0.1f);
    changed |= ImGui::DragFloat3(" Rotation axis", glm::value_ptr(rotationAxis), 0.1f);
    changed |= ImGui::DragFloat(" Rotation °", &rotationAngle, 0.1f);
    changed |= ImGui::DragFloat3(" Scaling", glm::value_ptr(scaleVector), 0.1f);

    if (changed) {
        selectedObj->updateModelMatrix(translation, rotationAxis, rotationAngle, scaleVector);
    }

    ImGui::NewLine();
    ImGui::Text("Meshes:");

    for (auto m : *selectedObj->getMeshes()) {
        if (ImGui::Button((m.first + " ->").c_str())) app.setSelectedMesh(selectedObj, m.first);
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

    Mesh* selectedMesh = get<1>(app.getScene()->getSelectedMesh());
    if (selectedMesh == nullptr) return;

    ImGui::SetNextWindowPos(ImVec2(objectInspectorSize.x + 2 * GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("MESH INSPECTOR", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Selected mesh:");
    ImGui::TextWrapped(get<0>(app.getScene()->getSelectedMesh()).c_str());
    ImGui::NewLine();

    // Shader selector
    map<string, Shader*>* shaders = app.getShaders();
    Shader* currentShader = selectedMesh->getCurrentShader();
    const char* previewName = "-----";

    if (shaders != nullptr) {
        for (const auto& s : *shaders) {
            if (s.second == currentShader) {
                previewName = s.first.c_str();
                break;
            }
        }
    }
    if (ImGui::BeginCombo(" Shader", previewName) && shaders != NULL) {
        for (const auto& s : *shaders) {
            bool isSelected = (currentShader == s.second);
            if (ImGui::Selectable(s.first.c_str(), isSelected)) selectedMesh->setShader(s.second);
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::NewLine();

    // Material selector
    map<string, Material*>* materials = app.getMaterials();
    Material* currentMaterial = selectedMesh->getCurrentMaterial();
    Material* fileLoadedMaterial = selectedMesh->getFileLoadedMaterial();
    Material* customMaterial = selectedMesh->getCustomMaterial();
    bool isCustomSelected = currentMaterial == customMaterial;
    previewName = "-----";
    if (materials != nullptr) {
        for (const auto& m : *materials) {
            if (m.second == currentMaterial) {
                previewName = m.first.c_str();
                break;
            }
        }
    }
    if (isCustomSelected) previewName = "Custom";
    if (ImGui::BeginCombo(" Material", currentMaterial == fileLoadedMaterial ? fileLoadedMaterial->getName().c_str() : previewName) && materials != NULL) {
        for (const auto& m : *materials) {
            bool isSelected = (currentMaterial == m.second);
            if (ImGui::Selectable(m.first.c_str(), isSelected)) selectedMesh->setMaterial(m.second);
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        if (fileLoadedMaterial != nullptr) {
            bool isSelected = (currentMaterial == fileLoadedMaterial);
            if (ImGui::Selectable(fileLoadedMaterial->getName().c_str(), isSelected)) selectedMesh->setMaterial(fileLoadedMaterial);
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        if (ImGui::Selectable(customMaterial->getName().c_str(), isCustomSelected)) selectedMesh->setMaterial(customMaterial);
        if (isCustomSelected) ImGui::SetItemDefaultFocus();
        ImGui::EndCombo();
    }

    if (isCustomSelected) {
        vec3 ambient = customMaterial->getAmbient(), diffuse = customMaterial->getDiffuse(), specular = customMaterial->getSpecular();
        float shininess = customMaterial->getShininess();
        ImGui::ColorEdit3(" Ambient", glm::value_ptr(ambient));
        ImGui::ColorEdit3(" Diffuse", glm::value_ptr(diffuse));
        ImGui::ColorEdit3(" Specular", glm::value_ptr(specular));
        ImGui::DragFloat(" Shininess", &shininess, 1, 1, 512);
        customMaterial->updateValues(ambient, diffuse, specular, shininess);
    }

    vec3 translation = selectedMesh->getTranslationVector();
    vec3 rotationAxis = selectedMesh->getRotationAxis();
    float rotationAngle = selectedMesh->getRotationAngle();
    vec3 scaleVector = selectedMesh->getScaleVector();

    ImGui::NewLine();
    ImGui::Text("Edit model matrix:");
    bool changed = false;

    changed |= ImGui::DragFloat3(" Position", glm::value_ptr(translation), 0.1f);
    changed |= ImGui::DragFloat3(" Rotation axis", glm::value_ptr(rotationAxis), 0.1f);
    changed |= ImGui::DragFloat(" Rotation °", &rotationAngle, 0.1f);
    changed |= ImGui::DragFloat3(" Scaling", glm::value_ptr(scaleVector), 0.1f);

    if (changed) {
        selectedMesh->updateModelMatrix(translation, rotationAxis, rotationAngle, scaleVector);
    }

    ImGui::NewLine();
    if (ImGui::Button("Close")) app.resetMeshSelection();
    ImGui::NewLine();
    
    ImGui::End();
}

void show_start_file_loading(const char* path) {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));

    ImGui::Begin("FILE LOADER", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Started loading mesh file:");
    ImGui::NewLine();
    ImGui::TextWrapped(path);
    
    ImGui::End();
}

void show_file_error(const char* path, const char* error) {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));

    ImGui::Begin("FILE LOADER", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Error loading file!");
    ImGui::NewLine();
    ImGui::TextWrapped("Error:\n%s", error);
    ImGui::NewLine();
    ImGui::TextWrapped("Path:\n%s", path);
    ImGui::NewLine();
    if (ImGui::Button("Ok")) app.confirmFileUploadError();

    ImGui::End();
}

void show_file_uploaded(const char* path, PhysicalObject* uploadedObject, char* nameBuffer) {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));

    ImGui::Begin("FILE LOADER", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("File uploaded!");
    ImGui::NewLine();
    ImGui::TextWrapped("Path:\n%s", path);

    ImGui::NewLine();
    ImGui::Text("Enter object name:");
    ImGui::InputText("", nameBuffer, MAX_LENGTH_OBJ_NAME);

    vec3 translation = uploadedObject->getTranslationVector();
    vec3 rotationAxis = uploadedObject->getRotationAxis();
    float rotationAngle = uploadedObject->getRotationAngle();
    vec3 scaleVector = uploadedObject->getScaleVector();

    ImGui::NewLine();
    ImGui::Text("Edit model matrix:");
    bool changed = false;

    changed |= ImGui::DragFloat3(" Position", glm::value_ptr(translation), 0.1f);
    changed |= ImGui::DragFloat3(" Rotation axis", glm::value_ptr(rotationAxis), 0.1f);
    changed |= ImGui::DragFloat(" Rotation °", &rotationAngle, 0.1f);
    changed |= ImGui::DragFloat3(" Scaling", glm::value_ptr(scaleVector), 0.1f);

    if (changed) {
        uploadedObject->updateModelMatrix(translation, rotationAxis, rotationAngle, scaleVector);
    }
    
    ImGui::NewLine();
    if (ImGui::Button("Ok")) {
        uploadedObject->setName(nameBuffer);
        app.confirmFileUploadSuccess();
    }

    ImGui::End();
}

void close_gui() {
    ImGui_ImplOpenGL3_Shutdown();   // Shut down the OpenGL integration
    ImGui_ImplGlfw_Shutdown();      // Shut down the GLFW integration
    ImGui::DestroyContext();        // Destroy the ImGui context
}
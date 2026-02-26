#include "gui.h"

#include <glm/gtc/type_ptr.hpp>

#include "../App.h"

using namespace std;

extern App app;
int status_bar_height = 0;

// Gui utility functions
void show_shader_selector(Mesh* selectedMesh);
void show_material_selector(Mesh* selectedMesh);
void show_texture_selector(Mesh* selectedMesh);
bool model_matrix_editor(vec3* translation, vec3* rotationAxis, float* rotationAngle, vec3* scaleVector);

void show_commands() {
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_FirstUseEver);

    ImGui::Begin("Commands", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("----- COMMANDS -----");
    ImGui::Text("O: Toggle objects list");
    ImGui::Text("L: Toggle light settings");
    ImGui::Text("P: Toggle pause and open / close settings");
    ImGui::Text("F1: Toggle commands window");
    ImGui::Text("F11: Toggle fullscreen mode");
    ImGui::Text("ESC: Go back to previous mode");
    ImGui::Text("Space bar: Toggle Picking / Navigation modes");
    ImGui::Text("Drag & Drop: Upload obj or texture file");
    ImGui::NewLine();
    ImGui::Text("----- CAMERA COMMANDS -----");
    ImGui::Text("W: Move forward");
    ImGui::Text("A: Move left");
    ImGui::Text("S: Move backward");
    ImGui::Text("D: Move right");
    ImGui::Text("E: Move up");
    ImGui::Text("Q: Move down");
    ImGui::Text("Arrows: Rotate camera");
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
        ImGui::GetIO().Framerate
    );

    status_bar_height = (int)ImGui::GetWindowSize().y;
    ImGui::End();
}

void show_settings() {

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(app.getWindowManager()->getCurrentResolution().x - 2 * GUI_WINDOWS_PADDING, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("PAUSE - Settings", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );
    ImGui::Text("MESH SETTINGS");
    ImGui::NewLine();

    bool boundingBox = app.getAppSettings()->isBoundingBoxActive();
    if (ImGui::Checkbox("Bounding Box", &boundingBox)) app.getAppSettings()->toggleBoundingBox();

    bool wireframe = app.getAppSettings()->isWireframeActive();
    if (ImGui::Checkbox("Wireframe", &wireframe)) app.getAppSettings()->toggleWireframe();

    bool anchor = app.getAppSettings()->isAnchorActive();
    if (ImGui::Checkbox("Anchor", &anchor)) app.getAppSettings()->toggleAnchor();

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("CAMERA SETTINGS");
    ImGui::NewLine();

    float tempFov = app.getAppSettings()->getCurrentFov();
    if (ImGui::SliderFloat(" FOV", &tempFov, PROJ_FOVY_MIN, PROJ_FOVY_MAX)) app.getAppSettings()->setFov(tempFov);

    float tempCameraSpeed = app.getAppSettings()->getCurrentCameraSpeed();
    if (ImGui::SliderFloat(" Camera Speed", &tempCameraSpeed, CAMERA_SPEED_MIN, CAMERA_SPEED_MAX)) app.getAppSettings()->setCameraSpeed(tempCameraSpeed);

    float tempTrackballSpeed = app.getAppSettings()->getCurrentTrackballSpeed();
    if (ImGui::SliderFloat(" Trackball Speed", &tempTrackballSpeed, TRACKBALL_SPEED_MIN, TRACKBALL_SPEED_MAX)) app.getAppSettings()->setTrackballSpeed(tempTrackballSpeed);

    float tempMouseSensitivity = app.getAppSettings()->getCurrentMouseSensitivity();
    if (ImGui::SliderFloat(" Mouse Sensitivity", &tempMouseSensitivity, MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX)) app.getAppSettings()->setMouseSensitivity(tempMouseSensitivity);

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("Press F1 to show the helper"); 
    ImGui::NewLine();
    if (ImGui::Button("Resume")) app.togglePause();
    if (ImGui::Button("Quit")) app.close();
    ImGui::NewLine();

    ImGui::End();
}

ImVec2 show_object_inspector() {

    PhysicalObject* selectedObj = app.getScene()->getSelectedObject();
    
    if (selectedObj == nullptr) return ImVec2(0, 0);
    
    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(app.getWindowManager()->getCurrentResolution().x / 2, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("OBJECT INSPECTOR", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("SELECTED OBJECT:");
    ImGui::TextWrapped(selectedObj->getName().c_str());
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    vec3 translation = selectedObj->getTranslationVector();
    vec3 rotationAxis = selectedObj->getRotationAxis();
    float rotationAngle = selectedObj->getRotationAngle();
    vec3 scaleVector = selectedObj->getScaleVector();

	if (model_matrix_editor(&translation, &rotationAxis, &rotationAngle, &scaleVector)) {
        selectedObj->updateModelMatrix(translation, rotationAxis, rotationAngle, scaleVector);
    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("%d Meshes:", selectedObj->getMeshes()->size());
    ImGui::NewLine();

    for (auto m : *selectedObj->getMeshes()) {
        if (ImGui::Button((m.first + " ->").c_str())) app.setSelectedMesh(selectedObj, m.first);
    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Delete")) {
        app.getScene()->removeObject(selectedObj);
        app.resetObjectSelection();
    }
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

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(app.getWindowManager()->getCurrentResolution().x - objectInspectorSize.x - 3 * GUI_WINDOWS_PADDING, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(objectInspectorSize.x + 2 * GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("MESH INSPECTOR", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("SELECTED MESH:");
    ImGui::TextWrapped(get<0>(app.getScene()->getSelectedMesh()).c_str());
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    vec3 translation = selectedMesh->getTranslationVector();
    vec3 rotationAxis = selectedMesh->getRotationAxis();
    float rotationAngle = selectedMesh->getRotationAngle();
    vec3 scaleVector = selectedMesh->getScaleVector();
 
    if (model_matrix_editor(&translation, &rotationAxis, &rotationAngle, &scaleVector)) {
        app.getScene()->getSelectedObject()->updateMeshModelMatrix(get<0>(app.getScene()->getSelectedMesh()), translation, rotationAxis, rotationAngle, scaleVector);
    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

	show_shader_selector(selectedMesh);
    if (selectedMesh->getGpuObject()->supportsMaterial()) show_material_selector(selectedMesh);
	if (selectedMesh->getGpuObject()->supportsTexture()) show_texture_selector(selectedMesh);

    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Delete")) {
        auto selectedObj = app.getScene()->getSelectedObject();
        selectedObj->removeMesh(selectedMesh);
        app.resetMeshSelection();
        if (selectedObj->getMeshes()->size() == 0) {
            app.getScene()->removeObject(selectedObj);
            app.escPressed();
        }
    }
    if (ImGui::Button("Close")) app.resetMeshSelection();
    ImGui::NewLine();
    
    ImGui::End();
}

void show_objects_list() {

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(app.getWindowManager()->getCurrentResolution().x - 2 * GUI_WINDOWS_PADDING, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("OBJECTS LIST", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );
    
    vector<PhysicalObject*>* objects = app.getScene()->getObjects();

    ImGui::NewLine();
    if (objects->size() > 0) {
        ImGui::Text("Select an object to open its inspector");
        ImGui::Text("Num. objects: %d", objects->size());
    }
    else ImGui::Text("The scene contains no objects!");
    ImGui::NewLine();

    int i = 0;
    char buffer[100];
    for (auto o : *objects) {
        sprintf_s(buffer, "%s##%d", o->getName().c_str(), i);
        if (ImGui::Button(buffer)) app.setSelectedObject(o);
        i++;
    }
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Close")) app.toggleObjectList();
    ImGui::NewLine();
    ImGui::End();
}

void show_start_file_loading(const char* path) {
    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(INFINITY, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
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

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(INFINITY, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));

    ImGui::Begin("FILE LOADER", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("ERROR LOADING FILE!");
    ImGui::NewLine();
    ImGui::TextWrapped("Error:\n%s", error);
    ImGui::NewLine();
    ImGui::TextWrapped("Path:\n%s", path);
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Ok")) app.confirmFileUploadError();

    ImGui::End();
}

void show_mesh_file_uploaded(const char* path, PhysicalObject* uploadedObject, char* nameBuffer) {

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(INFINITY, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));

    ImGui::Begin("FILE LOADER", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("FILE UPLOADED!");
    ImGui::NewLine();
    ImGui::TextWrapped("Path:\n%s", path);

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("Enter object name:");
    ImGui::NewLine();
    ImGui::InputText("", nameBuffer, MAX_LENGTH_OBJ_NAME);

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    vec3 translation = uploadedObject->getTranslationVector();
    vec3 rotationAxis = uploadedObject->getRotationAxis();
    float rotationAngle = uploadedObject->getRotationAngle();
    vec3 scaleVector = uploadedObject->getScaleVector();

    if (model_matrix_editor(&translation, &rotationAxis, &rotationAngle, &scaleVector)) {
        uploadedObject->updateModelMatrix(translation, rotationAxis, rotationAngle, scaleVector);
    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Ok")) {
        uploadedObject->setName(nameBuffer);
        app.confirmFileUploadSuccess();
    }

    ImGui::End();
}

void show_texture_file_uploaded(const char* path, Texture* uploadedTexture, char* nameBuffer) {

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, 0.0f), // No min size
        ImVec2(INFINITY, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(app.getWindowManager()->getCurrentResolution().x - GUI_WINDOWS_PADDING * 2, 0.0f));

    ImGui::Begin("FILE LOADER", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );

    ImGui::Text("TEXTURE UPLOADED!");
    ImGui::NewLine();
    ImGui::TextWrapped("Path:\n%s", path);

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("Enter texture name:");
    ImGui::NewLine();
    ImGui::InputText("", nameBuffer, MAX_LENGTH_OBJ_NAME);
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    ImGui::Text("Preview:");
    ImGui::NewLine();
    ImTextureID imguiTexID = (ImTextureID)(intptr_t)uploadedTexture->getProgramId();
    ImVec2 previewSize(100, 100);
    ImGui::Image(imguiTexID, previewSize);

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Ok")) {
        string finalName = nameBuffer;
        int counter = 1;

        // Check for duplicate names and increment the counter
        while (app.getTextures()->find(finalName) != app.getTextures()->end()) {
            finalName = string(nameBuffer) + "#" + to_string(counter);
            counter++;
        }
        uploadedTexture->setName(finalName);
        app.confirmFileUploadSuccess();
    }
    ImGui::End();
}

void show_light_settings() {

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(350.0f, 0.0f), // No min y size
        ImVec2(app.getWindowManager()->getCurrentResolution().x - 2 * GUI_WINDOWS_PADDING, app.getWindowManager()->getCurrentResolution().y - status_bar_height - 3 * GUI_WINDOWS_PADDING)
    );
    ImGui::SetNextWindowPos(ImVec2(GUI_WINDOWS_PADDING, GUI_WINDOWS_PADDING), ImGuiCond_Always);

    ImGui::Begin("LIGHT SETTINGS", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
    );
    
    ImGui::NewLine();
    vector<PointLight*>* lights = app.getScene()->getLights();

    if (lights->size() < MAX_LIGHTS) {
        if (ImGui::Button("Add point light")) app.getScene()->createLight();
    }
    else {
        ImGui::Text("Max lights reached");
    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    for (int i = 0; i < lights->size(); i++) {
        char buffer[100];
        sprintf_s(buffer, "Light #%d", i);
        if (ImGui::CollapsingHeader(buffer)) {
            vec3 pos = lights->at(i)->getPosition();
            vec3 color = lights->at(i)->getColor();
            float power = lights->at(i)->getPower();
            sprintf_s(buffer, " Position##%d", i);
            if (ImGui::DragFloat3(buffer, glm::value_ptr(pos), 0.1f)) lights->at(i)->setPosition(pos);
            sprintf_s(buffer, " Color##%d", i);
            if (ImGui::ColorEdit3(buffer, glm::value_ptr(color))) lights->at(i)->setColor(color);
            sprintf_s(buffer, " Power##%d", i);
            if (ImGui::SliderFloat(buffer, &power, MIN_LIGHT_POWER, MAX_LIGHT_POWER)) lights->at(i)->setPower(power);
            sprintf_s(buffer, "Remove##%d", i);
            if (ImGui::Button(buffer)) app.getScene()->removeLight(i);
            ImGui::NewLine();
        }
    }

    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();
    if (ImGui::Button("Close")) app.toggleLightSettings();
    ImGui::NewLine();

    ImGui::End();
}

void close_gui() {
    ImGui_ImplOpenGL3_Shutdown();   // Shut down the OpenGL integration
    ImGui_ImplGlfw_Shutdown();      // Shut down the GLFW integration
    ImGui::DestroyContext();        // Destroy the ImGui context
}


void show_shader_selector(Mesh* selectedMesh) {
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
    if (ImGui::BeginCombo(" Shading", previewName) && shaders != NULL) {
        for (const auto& s : *shaders) {
            bool isSelected = (currentShader == s.second);
            if (ImGui::Selectable(s.first.c_str(), isSelected)) selectedMesh->setShader(s.second);
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::NewLine();

    if (selectedMesh->getGpuObject()->canUseBlinnPhong()) {
        ImGui::Text("Illumination model:");
        int usingBlinnPhong = selectedMesh->getGpuObject()->isUsingBlinnPhong();
        ImGui::RadioButton("Phong", &usingBlinnPhong, false); ImGui::SameLine();
        ImGui::RadioButton("Blinn - Phong", &usingBlinnPhong, true);
        ImGui::NewLine();
        selectedMesh->getGpuObject()->setBlinnPhong(usingBlinnPhong);
    }
}

void show_material_selector(Mesh* selectedMesh) {
    map<string, Material*>* materials = app.getMaterials();
    Material* currentMaterial = selectedMesh->getCurrentMaterial();
    Material* fileLoadedMaterial = selectedMesh->getFileLoadedMaterial();
    Material* customMaterial = selectedMesh->getCustomMaterial();
    bool isCustomSelected = currentMaterial == customMaterial;
    const char* previewName = "-----";
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
    ImGui::NewLine();

}

void show_texture_selector(Mesh* selectedMesh) {
    map<string, Texture*>* textures = app.getTextures();
    Texture* currentTexture = selectedMesh->getCurrentTexture();
    const char *previewName = "None";

    if (textures != nullptr) {
        for (const auto& t : *textures) {
            if (t.second == currentTexture) {
                previewName = t.first.c_str();
                break;
            }
        }
    }
    if (ImGui::BeginCombo(" Texture", previewName) && textures != NULL) {
        bool isNone = (currentTexture == nullptr);
        if (ImGui::Selectable("None", isNone)) selectedMesh->setTexture(nullptr);
        if (isNone) ImGui::SetItemDefaultFocus();

        for (const auto& t : *textures) {
            bool isSelected = (currentTexture == t.second);
            if (ImGui::Selectable(t.first.c_str(), isSelected)) selectedMesh->setTexture(t.second);
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    if (currentTexture != nullptr) {
        ImGui::NewLine();
        ImGui::Text("Texture preview:");
        ImTextureID imguiTexID = (ImTextureID)(intptr_t)currentTexture->getProgramId();
        ImVec2 previewSize(100, 100);
        ImGui::Image(imguiTexID, previewSize);
    }
    ImGui::NewLine();
}

bool model_matrix_editor(vec3* translation, vec3* rotationAxis, float* rotationAngle, vec3* scaleVector) {
    if (ImGui::CollapsingHeader("Edit model matrix  ")) {
        ImGui::NewLine();
        bool changed = false;

        changed |= ImGui::DragFloat3(" Position", glm::value_ptr(*translation), 0.1f);
        changed |= ImGui::DragFloat3(" Rotation axis", glm::value_ptr(*rotationAxis), 0.1f);
        changed |= ImGui::DragFloat(" Rotation °", rotationAngle, 0.1f);
        changed |= ImGui::DragFloat3(" Scaling", glm::value_ptr(*scaleVector), 0.1f);

        return changed;
    }

    return false;
}

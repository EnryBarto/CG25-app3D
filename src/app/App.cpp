#include "App.h"

#include <system_error>
#include "initializations.h"
#include "gui.h"
#include "../settings.h"
#include <cstdlib>
#include <ctime>

App::App() {
	this->windowManager = new WindowManager();
	if (this->windowManager->getWindow() == NULL) {
		throw std::runtime_error("Window initialization failed");
	} else {
		cout << "Window initialized" << endl;
	}

	this->shaders = init_shaders();
	if (this->shaders == NULL) {
		throw std::runtime_error("Shaders initialization failed!");
	} else {
		cout << "Shaders initialized" << endl;
	}

	this->materials = init_materials();

	this->currentSettings = new AppSettings();
	this->scene = new Scene(windowManager, currentSettings, shaders->at(INTERPOLATION_SHADER_NAME), shaders->at(BASIC_SHADER_NAME), materials->at(NO_MATERIAL_NAME), shaders->at(CUBEMAP_SHADER_NAME), SKYBOX_CUBEMAP_DIRECTORY);

    // Assign random materials
    std::vector<Material*> matList;
    for (auto const& p : *this->materials) if (p.first != NO_MATERIAL_NAME) matList.push_back(p.second);
    if (!matList.empty()) {
        std::srand((unsigned)std::time(nullptr));
        for (PhysicalObject* obj : this->scene->objects) {
            for (auto &me : *obj->getMeshes()) {
                me.second->setMaterial(matList[std::rand() % matList.size()]);
            }
        }
    }

	this->nextState = AppState::PAUSED;
	this->currentState = AppState::NAVIGATION;
	this->statesHistory.push(AppState::NAVIGATION);
}

App::~App() {
    close_gui();
    delete scene;

	for (auto const& s : *shaders) {
		delete s.second;
	}
	delete shaders;
	
	for (auto const& m : *materials) {
		delete m.second;
	}
	delete materials;

    delete currentSettings;

    glfwDestroyWindow(this->windowManager->getWindow());
    glfwTerminate();

    delete windowManager;
}

void App::update(float deltaTime) {
	if (glfwWindowShouldClose(this->windowManager->getWindow())) this->close();
	this->loopFileUpload(); // Check if there are files to upload
	if (this->currentState != this->nextState) {
		switch (this->nextState) {
			case AppState::NAVIGATION:
				glfwSetInputMode(this->windowManager->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
			default:
				glfwSetInputMode(this->windowManager->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
		}
		this->currentState = this->nextState;
	}
	scene->update((float)deltaTime, this->currentState);
}

void App::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// GUI Setting
	ImGui_ImplGlfw_NewFrame();          // Prepare a new frame for GLFW input
	ImGui_ImplOpenGL3_NewFrame();       // Prepare a new frame for OpenGL3 rendering
	ImGui::NewFrame();                  // Begin recording the new UI frame

	// 3D Objects rendering
	this->scene->render();

	// Gui Rendering
	switch (this->currentState) {
		case AppState::PAUSED: show_settings(); break;
		case AppState::LOADING_FILES: case AppState::FILE_LOAD: show_start_file_loading(this->filesToLoad.front().c_str()); break;
		case AppState::WAIT_FILE_ABORT: show_file_error(this->filesToLoad.front().c_str(), this->stringBuffer); break;
		case AppState::WAIT_FILE_CONFIRM: show_file_uploaded(this->filesToLoad.front().c_str(), this->scene->getSelectedObject(), this->stringBuffer); break;
		case AppState::EDITING_OBJ: show_object_inspector(); break;
		case AppState::EDITING_MESH: show_mesh_inspector(); break;
		case AppState::LIGHT_SETTINGS: show_light_settings(); break;
	}
	show_status_bar();
	if (this->currentSettings->isShowingCommands()) show_commands();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(this->windowManager->getWindow());
	glfwPollEvents();
}

void App::close() {
	this->nextState = AppState::CLOSED;
}

AppState App::getCurrentAppState() {
	return this->currentState;
}

void App::togglePause() {
	switch (this->currentState) {
		case AppState::WAIT_FILE_CONFIRM:
			// Do nothing: The user is using the keyboard to write the object name
			break;
		case AppState::PAUSED:
			this->setNextStateFromHistory();
			break;
		default:
			this->nextState = AppState::PAUSED;
			this->statesHistory.push(this->currentState);
			break;
	}
}

void App::toggleMode() {
	switch (this->currentState) {
		case AppState::NAVIGATION:
			this->nextState = AppState::PICKING;
			break;
		case AppState::PICKING:
			this->nextState = AppState::NAVIGATION;
			break;
		default:
			break;
	}
}

void App::escPressed() {
	switch (this->currentState) {
		case AppState::FILE_LOAD:
		case AppState::WAIT_FILE_CONFIRM:
			// Do nothing
			break;
		case AppState::WAIT_FILE_ABORT:
			this->confirmFileUploadError();
			break;
		default:
			if (!this->statesHistory.empty()) this->setNextStateFromHistory();
			break;
	}
}

map<string, Shader*>* App::getShaders() {
	return this->shaders;
}

map<string, Material*>* App::getMaterials() {
	return this->materials;
}

void App::toggleLightSettings() {
	switch (this->currentState) {
		case AppState::PAUSED:
			// Do nothing
			break;
		case AppState::LIGHT_SETTINGS:
			this->setNextStateFromHistory();
			break;
		default:
			this->nextState = AppState::LIGHT_SETTINGS;
			this->statesHistory.push(this->currentState);
			break;
	}
}

void App::loadObjectsFromFile(const char* paths[], int numFiles) {
	if (this->currentState == AppState::NAVIGATION || this->currentState == AppState::PICKING) {
		for (int i = 0; i < numFiles; i++) {
			this->filesToLoad.push(paths[i]);
		}
	}
}

void App::confirmFileUploadError() {
	this->filesToLoad.pop();
	this->nextState = AppState::LOADING_FILES;
}

void App::confirmFileUploadSuccess() {
	this->filesToLoad.pop();
	this->nextState = AppState::LOADING_FILES;
	this->scene->resetObjectSelection();
}

WindowManager* App::getWindowManager() {
	return this->windowManager;
}

Scene* App::getScene() {
	return this->scene;
}

AppSettings* App::getAppSettings() {
	return this->currentSettings;
}

void App::setSelectedObject(PhysicalObject* selected) {
	if (this->scene->setSelectedObject(selected)) {
		this->statesHistory.push(this->currentState);
		this->nextState = AppState::EDITING_OBJ;
	}
}

void App::setSelectedMesh(PhysicalObject* selectedObject, string selectedMesh) {
	if (this->scene->setSelectedMesh(selectedObject, selectedMesh)) {
		if (this->currentState != AppState::EDITING_OBJ && this->currentState != AppState::EDITING_MESH) this->statesHistory.push(this->currentState);
		if (this->currentState != AppState::EDITING_MESH) this->statesHistory.push(AppState::EDITING_OBJ);
		this->nextState = AppState::EDITING_MESH;
	}
}

void App::pick(vec2 clickPosition) {
	tuple<PhysicalObject*, string> selected = this->scene->mousePicked(clickPosition);
	if (get<0>(selected) != nullptr && get<1>(selected) != "") {
		this->setSelectedMesh(get<0>(selected), get<1>(selected));
	}
}

void App::resetObjectSelection() {
	if (this->currentState == AppState::EDITING_MESH) this->statesHistory.pop();
	this->setNextStateFromHistory();
	this->scene->resetObjectSelection();
}

void App::resetMeshSelection() {
	this->setNextStateFromHistory();
	this->scene->resetMeshSelection();
}

void App::setNextStateFromHistory() {
	this->nextState = this->statesHistory.top();
	this->statesHistory.pop();
}

void App::loopFileUpload() {
	if (this->currentState == AppState::NAVIGATION || this->currentState == AppState::PICKING) {
		if (this->filesToLoad.size() > 0) {
			this->nextState = AppState::LOADING_FILES;
			this->statesHistory.push(this->currentState);
		}
	}
	if (currentState == AppState::LOADING_FILES) {
		if (this->filesToLoad.size() == 0) {
			this->setNextStateFromHistory();
		} else {
			this->nextState = AppState::FILE_LOAD;
		}
	}
	if (this->currentState == AppState::FILE_LOAD) {
		string file = this->filesToLoad.front();
		if (file.substr(file.size() - 4) == ".obj") {
			PhysicalObject* loaded = this->scene->loadObjectFromFile(file.c_str());
			if (loaded != nullptr) {
				this->nextState = AppState::WAIT_FILE_CONFIRM;
				this->scene->setSelectedObject(loaded);
				strcpy_s(this->stringBuffer, loaded->getName().c_str());
			} else {
				this->nextState = AppState::WAIT_FILE_ABORT;
				strcpy_s(this->stringBuffer, "Error creating object");
			}
		} else if (file.substr(file.size() - 4) == ".mtl") { // Ignore mtl files
			this->filesToLoad.pop();
			this->nextState = AppState::LOADING_FILES;
		} else {
			this->nextState = AppState::WAIT_FILE_ABORT;
			strcpy_s(this->stringBuffer, "The file is not .obj");
		}
	}
}


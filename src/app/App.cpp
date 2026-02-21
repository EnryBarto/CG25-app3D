#include "App.h"

#include <system_error>
#include "initializations.h"
#include "gui.h"
#include "../settings.h"

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

	this->currentSettings = new AppSettings();
	this->scene = new Scene(windowManager, currentSettings, shaders->at(BASIC_SHADER_NAME), shaders->at(CUBEMAP_SHADER_NAME), SKYBOX_CUBEMAP_DIRECTORY);

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

    delete currentSettings;

    glfwDestroyWindow(this->windowManager->getWindow());
    glfwTerminate();

    delete windowManager;
}

void App::update(float deltaTime) {
	if (glfwWindowShouldClose(this->windowManager->getWindow())) this->close();
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

	// GUI 
	ImGui_ImplGlfw_NewFrame();          // Prepare a new frame for GLFW input
	ImGui_ImplOpenGL3_NewFrame();       // Prepare a new frame for OpenGL3 rendering
	ImGui::NewFrame();                  // Begin recording the new UI frame

	this->scene->render();

	show_status_bar();
	if (this->currentState != AppState::PAUSED) {
		if (this->currentState == AppState::EDITING_OBJ) show_object_inspector();
		if (this->currentState == AppState::EDITING_MESH) show_mesh_inspector();
	}
	if (this->currentState == AppState::PAUSED) show_settings();
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
		case AppState::PAUSED:
			this->nextState = this->statesHistory.top();
			this->statesHistory.pop();
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
	if (!this->statesHistory.empty()) {
		this->setNextStateFromHistory();
	}
}

map<string, Shader*>* App::getShaders() {
	return this->shaders;
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

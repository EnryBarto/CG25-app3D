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

	this->currentState = AppState::PAUSED;
	this->precState = AppState::NAVIGATION;
	glfwSetInputMode(this->windowManager->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
	if (this->currentState == AppState::PAUSED) show_settings();
	if (this->currentSettings->isShowingCommands()) show_commands();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(this->windowManager->getWindow());
	glfwPollEvents();
}

void App::close() {
	this->currentState = AppState::CLOSED;
}

AppState App::getCurrentAppState() {
	return this->currentState;
}

void App::togglePause() {
	switch (this->currentState) {
		case AppState::PAUSED:
			this->currentState = this->precState;
			this->precState = AppState::PAUSED;
			break;
		default:
			this->precState = this->currentState;
			this->currentState = AppState::PAUSED;
			glfwSetInputMode(this->windowManager->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
	}
}

void App::toggleMode() {
	switch (this->currentState) {
		case AppState::NAVIGATION:
			this->currentState = AppState::PICKING;
			this->precState = AppState::NAVIGATION;
			glfwSetInputMode(this->windowManager->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case AppState::PICKING:
			this->currentState = AppState::NAVIGATION;
			this->precState = AppState::PICKING;
			break;
		default:
			break;
	}
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

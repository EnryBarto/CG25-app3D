#include <iostream>
#include <chrono>
#include <thread>
#include "src/app/initializations.h"
#include "src/app/gui.h"
#include <map>
#include "src/settings.h"
#include "src/graphics/shader/Shader.h"
#include "src/graphics/Scene.h"
#include "src/graphics/WindowManager.h"
#include "src/app/AppSettings.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

WindowManager* windowManager;
GLFWwindow* window;
Scene* scene;
Camera* camera;
AppSettings* currentSettings;
map<string, Shader*>* shaders;
double currentTime, deltaTime = 0, lastFrame = 0;

int main() {
	
	windowManager = new WindowManager();
	window = windowManager->getWindow();
	if (window == NULL) {
		cout << "Window initialization failed!" << endl;
		return -1;
	} else {
		cout << "Window initialized" << endl;
	}

	shaders = init_shaders();
	if (shaders == NULL) {
		cout << "Shaders initialization failed!" << endl;
		return -1;
	} else {
		cout << "Shaders initialized" << endl;
	}
	currentSettings = new AppSettings();
	scene = new Scene(windowManager, currentSettings, shaders->at(BASIC_SHADER_NAME), shaders->at(CUBEMAP_SHADER_NAME), SKYBOX_CUBEMAP_DIRECTORY);
	camera = scene->getCamera();
	
	while (!glfwWindowShouldClose(window) && currentSettings->isActive()) {

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		scene->update((float)deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// GUI 
		ImGui_ImplGlfw_NewFrame();          // Prepare a new frame for GLFW input
		ImGui_ImplOpenGL3_NewFrame();       // Prepare a new frame for OpenGL3 rendering
		ImGui::NewFrame();                  // Begin recording the new UI frame

		scene->render();

		if (currentSettings->isPaused()) show_settings();
		if (currentSettings->isShowingCommands()) show_commands();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		// FPS limiter
		sleep_for(milliseconds(1000 / MAX_FPS) - milliseconds((int)(deltaTime * 1000)));
	}

	close_gui();
	glfwDestroyWindow(window);
	for (auto const& s : *shaders) {
		glDeleteProgram(s.second->getProgramId());
	}
	glfwTerminate();

	return 0;
}
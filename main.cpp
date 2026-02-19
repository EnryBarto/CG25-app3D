#include <iostream>
#include <chrono>
#include <thread>
#include "src/app/initializations.h"
#include "src/app/gui.h"
#include <map>
#include "src/settings.h"
#include "src/graphics/shader/Shader.h"
#include "src/graphics/Scene.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

GLFWwindow* window;
Scene* scene;
map<string, Shader*>* shaders;
double currentTime, deltaTime = 0, lastFrame = 0;
MessageBus* messageBus;

int main() {
	
	window = create_window();
	if (window == NULL) {
		cout << "Initialization failed!" << endl;
		return -1;
	} else {
		cout << "Window initialized" << endl;
	}

	shaders = init_shaders();
	if (shaders != NULL) {
		cout << "Shaders initialized" << endl;
	}

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	scene = new Scene(width, height, shaders->at(BASIC_SHADER_NAME), shaders->at(CUBEMAP_SHADER_NAME), SKYBOX_CUBEMAP_DIRECTORY);
	messageBus = scene->getMessageBus();

	while (!glfwWindowShouldClose(window)) {

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		scene->update((float)deltaTime);

		scene->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		// FPS limiter
		sleep_for(milliseconds(1000 / MAX_FPS) - milliseconds((int)(deltaTime * 1000)));
	}

	close_gui();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/App.h"
#include "src/utils/AppState.h"

App app;
double currentTime, deltaTime = 0, lastFrame = 0;

int main() {

	while (app.getCurrentAppState() != AppState::CLOSED) {

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		app.update((float)deltaTime);

		app.render();
	}

	// Deallocation of all resources is done automatically by the App class destructor

	return 0;
}
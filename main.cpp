#include <chrono>
#include <thread>
#include "src/app/App.h"
#include "src/app/AppState.h"
#include "src/settings.h"
#include "GLFW/glfw3.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

App app;
double currentTime, deltaTime = 0, lastFrame = 0;

int main() {

	while (app.getCurrentAppState() != AppState::CLOSED) {

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		app.update((float)deltaTime);

		app.render();
		
		// FPS limiter
		sleep_for(milliseconds(1000 / MAX_FPS) - milliseconds((int)(deltaTime * 1000)));
	}

	// Deallocation of all resources is done automatically by the App class destructor

	return 0;
}
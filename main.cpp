#include <iostream>

#include "src/app/initializations.h"
#include "src/app/gui.h"
#include <map>
#include "src/graphics/shader/Shader.h"

using namespace std;

GLFWwindow* window;
map<string, Shader*>* shaders;

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

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	close_gui();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
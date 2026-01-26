#include <iostream>

#include "src/app/initializations.h"
#include "src/app/gui.h"

GLFWwindow* window;

int main() {
	
	window = initialize_all();

	if (window == NULL) {
		std::cout << "Initialization failed!" << std::endl;
		return -1;
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
#include <iostream>

#include "src/app/initializations.h"
#include "src/app/gui.h"
#include <map>
#include "src/graphics/shader/Shader.h"
#include "src/graphics/Scene.h"

using namespace std;

GLFWwindow* window;
Scene* scene;
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

	int height, width;
	glfwGetWindowSize(window, &width, &height);
	scene = new Scene(width, height, shaders->at(CUBEMAP_SHADER_NAME), SKYBOX_CUBEMAP_DIRECTORY);

	while (!glfwWindowShouldClose(window)) {
		scene->render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	close_gui();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
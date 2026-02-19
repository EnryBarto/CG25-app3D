#include "Scene.h"

Scene::Scene(GLFWwindow* window, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory) {
	this->window = window;
	this->camera = new Camera(vec3(0.0, 0.0, -10.0), vec3(0.0, 0.0, 20.0), vec3(0.0, 1.0, 0.0));
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	this->projection = new Projection(width, height);
	this->skybox = new Skybox(skyboxShader, skyboxCubemapDirectory);
	this->objectFactory = new PhysicalObjectFactory(defaultShader);
	this->objects.push_back(this->objectFactory->createBase());
	this->objects.push_back(this->objectFactory->createSimpleCube());
	this->objects.push_back(this->objectFactory->createHouse());
}

void Scene::update(float deltaTime) {
    if (this->messageBus.isAspectRatioChanged()) this->projection->changeAspectRatio(this->messageBus.getNewAspectRatio());
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) this->camera->moveLeft(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) this->camera->moveRight(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) this->camera->moveForward(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) this->camera->moveBack(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS && (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)) this->camera->moveDown(deltaTime);
	else if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS) this->camera->moveUp(deltaTime);
}

void Scene::render() {
	const mat4& v = this->camera->getViewMatrix();
	const mat4& p = this->projection->getProjectionMatrix();
	const vec3& c = this->camera->getPosition();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->skybox->render(v, p);
	for (PhysicalObject* o : this->objects) {
		o->render(v, p, c);
	}
}

MessageBus* Scene::getMessageBus() {
	return &this->messageBus;
}

#include "Scene.h"

Camera* campp;

Scene::Scene(WindowManager* windowManager, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory) {
	this->windowManager = windowManager;
	this->window = windowManager->getWindow();
	this->camera = new Camera(vec3(0.0, 0.0, -10.0), vec3(0.0, 0.0, 20.0));
	this->projection = new Projection(windowManager->getAspectRatio());
	this->skybox = new Skybox(skyboxShader, skyboxCubemapDirectory);
	this->objectFactory = new PhysicalObjectFactory(defaultShader);
	this->objects.push_back(this->objectFactory->createBase());
	this->objects.push_back(this->objectFactory->createSimpleCube());
	this->objects.push_back(this->objectFactory->createHouse());
	campp = this->camera;
}

Camera* Scene::getCamera() {
	return this->camera;
}

void Scene::update(float deltaTime) {
    if (this->windowManager->isFrameBufferChanged()) this->projection->changeAspectRatio(this->windowManager->getAspectRatio());
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) this->camera->moveLeft(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) this->camera->moveRight(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) this->camera->moveForward(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) this->camera->moveBack(deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_Y) == GLFW_PRESS) this->camera->moveDown(deltaTime);
	if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS) this->camera->moveUp(deltaTime);
}

void Scene::render() {
	const mat4& v = this->camera->getViewMatrix();
	const mat4& p = this->projection->getProjectionMatrix();
	const vec3& c = this->camera->getPosition();

	this->skybox->render(v, p);
	for (PhysicalObject* o : this->objects) {
		o->render(v, p, c);
	}
}
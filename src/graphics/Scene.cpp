#include "Scene.h"

Scene::Scene(WindowManager* windowManager, AppSettings* currentSettings, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory) {
	this->windowManager = windowManager;
	this->window = windowManager->getWindow();
	this->currentSettings = currentSettings;
	this->camera = new Camera(vec3(0, 6, -10), vec3(0, 0, 20), this->currentSettings->getCurrentCameraSpeed());
	this->projection = new Projection(windowManager->getAspectRatio(), this->currentSettings->getCurrentFov());
	this->skybox = new Skybox(skyboxShader, skyboxCubemapDirectory);
	this->objectFactory = new PhysicalObjectFactory(defaultShader);
	this->objects.push_back(this->objectFactory->createBase());
	this->objects.push_back(this->objectFactory->createSimpleCube(vec3(2, 0, 8)));
	this->objects.push_back(this->objectFactory->createSimpleSphere(vec3(9, 0, 3)));
	this->objects.push_back(this->objectFactory->createHouse(vec3(-5, 0, 4)));
	this->objects.push_back(this->objectFactory->createSimpleCone(vec3(8, 0, -2)));
	this->objects.push_back(this->objectFactory->createSimpleTorus(vec3(-6, 0, -3)));
	this->objects.push_back(this->objectFactory->createSimpleCylinder(vec3(3, 0, 2)));
}

Camera* Scene::getCamera() {
	return this->camera;
}

void Scene::update(float deltaTime) {

	// Updates to check only if the app isn't paused
	if (!currentSettings->isPaused()) {
		if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) this->camera->moveLeft(deltaTime);
		if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) this->camera->moveRight(deltaTime);
		if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) this->camera->moveForward(deltaTime);
		if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) this->camera->moveBack(deltaTime);
		if (glfwGetKey(this->window, GLFW_KEY_Y) == GLFW_PRESS) this->camera->moveDown(deltaTime);
		if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS) this->camera->moveUp(deltaTime);
	}

    if (this->windowManager->isFrameBufferChanged()) this->projection->changeAspectRatio(this->windowManager->getAspectRatio());
	if (this->currentSettings->isFovChanged()) this->projection->changeFov(this->currentSettings->getCurrentFov());
	if (this->currentSettings->isCameraSpeedChanged()) this->camera->setSpeed(this->currentSettings->getCurrentCameraSpeed());
}

void Scene::render() {
	const mat4& v = this->camera->getViewMatrix();
	const mat4& p = this->projection->getProjectionMatrix();
	const vec3& c = this->camera->getPosition();
	bool anchor	  = this->currentSettings->isAnchorActive();

	// Set the polygon mode if it was changed
	if (this->currentSettings->isWireframeActiveChanged()) {
		if (this->currentSettings->isWireframeActive()) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		this->currentSettings->setWireframeUnchanged();
	}

	// Actual rendering phase
	this->skybox->render(v, p);
	for (PhysicalObject* o : this->objects) {
		o->render(v, p, c, anchor);
	}
}
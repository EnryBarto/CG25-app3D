#include "Scene.h"

Scene::Scene(int screenWidth, int screenHeight, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory) {
	this->camera = new Camera(vec3(0.0, 0.0, -10.0), vec3(0.0, 0.0, 20.0), vec3(0.0, 1.0, 0.0));
	this->projection = new Projection(screenWidth, screenHeight);
	this->skybox = new Skybox(skyboxShader, skyboxCubemapDirectory);
	this->objectFactory = new PhysicalObjectFactory(defaultShader);
	this->objects.push_back(this->objectFactory->createBase());
	this->objects.push_back(this->objectFactory->createSimpleCube());
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
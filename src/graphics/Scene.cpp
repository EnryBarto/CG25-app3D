#include "Scene.h"

Scene::Scene(int screenWidth, int screenHeight, Shader* skyboxShader, string skyboxCubemapDirectory) {
	this->camera = new Camera(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 20.0), vec3(0.0, 1.0, 0.0));
	this->projection = new Projection(screenWidth, screenHeight);
	this->skybox = new Skybox(skyboxShader, skyboxCubemapDirectory);
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mat4 v = this->camera->getViewMatrix();
	mat4 p = this->projection->getProjectionMatrix();
	this->skybox->render(&v, &p);
}

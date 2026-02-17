#include "Scene.h"

Scene::Scene(int screenWidth, int screenHeight) {
	this->camera = new Camera(vec3(0.0, 100.0, 20.0), vec3(10.0, -300.0, 10.0), vec3(0.0, 1.0, 0.0));
	this->projection = new Projection(screenWidth, screenHeight);
}

void Scene::render() {
}

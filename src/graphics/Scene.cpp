#include "Scene.h"
#include <limits>
#include <algorithm>

Scene::Scene(WindowManager* windowManager, AppSettings* currentSettings, Shader* defaultShader, Shader* lightShader, Material* defaultMaterial, Shader* skyboxShader, string skyboxCubemapDirectory) {
	this->windowManager = windowManager;
	this->window = windowManager->getWindow();
	this->currentSettings = currentSettings;
	this->camera = new Camera(vec3(0, 6, -10), vec3(0, 0, 20), this->currentSettings->getCurrentCameraSpeed());
	this->projection = new Projection(windowManager->getAspectRatio(), this->currentSettings->getCurrentFov());
	this->skybox = new Skybox(skyboxShader, skyboxCubemapDirectory);
	this->objectFactory = new PhysicalObjectFactory(defaultShader, defaultMaterial);
	this->objects.push_back(this->objectFactory->createBase());
	this->objects.push_back(this->objectFactory->createSimpleCube(vec3(2, 0, 8)));
	this->objects.push_back(this->objectFactory->createSimpleSphere(vec3(9, 0, 3)));
	this->objects.push_back(this->objectFactory->createHouse(vec3(-5, 0, 4)));
	this->objects.push_back(this->objectFactory->createSimpleCone(vec3(8, 0, -2)));
	this->objects.push_back(this->objectFactory->createSimpleTorus(vec3(-6, 0, -3)));
	this->objects.push_back(this->objectFactory->createSimpleCylinder(vec3(3, 0, 2)));
	this->lightShader = lightShader;
	this->lights.push_back(new PointLight(vec3(-500, 200, -1000), vec4(1), 2, this->lightShader));
	this->lights.push_back(new PointLight(vec3(15, 20, 15), vec4(1), 0.7f, this->lightShader));
	this->lights.push_back(new PointLight(vec3(-15, 20, 15), vec4(1), 0.7f, this->lightShader));
	this->lights.push_back(new PointLight(vec3(15, 20, -15), vec4(1), 0.7f, this->lightShader));
	this->lights.push_back(new PointLight(vec3(-15, 20, -15), vec4(1), 0.7f, this->lightShader));
}

Scene::~Scene() {
	for (PhysicalObject* o : this->objects) delete o;
	delete this->camera;
	delete this->projection;
	delete this->skybox;
	delete this->objectFactory;
}

Camera* Scene::getCamera() {
	return this->camera;
}

void Scene::update(float deltaTime, AppState currentState) {

	// Activate camera moving only when in navigation or picking
	if (currentState == AppState::NAVIGATION || currentState == AppState::PICKING) {
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
	for (PointLight* l : this->lights) {
		l->render(v, p);
	}
	for (PhysicalObject* o : this->objects) {
		o->render(v, p, c, anchor, &this->lights);
	}
}

vector<PointLight*>* Scene::getLights() {
	return &this->lights;
}

vec3 Scene::getRayFromMouseClick(vec2 clickPosition) {
	clickPosition.y = this->windowManager->getCurrentResolution().y - clickPosition.y;

	// Map viewport coordinates [0,width], [0,height] in NDC [-1,1]  
	clickPosition = 2.0f * clickPosition / this->windowManager->getCurrentResolution() - 1.0f;

	// In clip space a smaller z means the object is closer to the camera, so we set z to -1
	// to place the point on the near plane of the frustum.
	// This means the ray we compute will start from the camera and go towards
	// the nearest visible point on the screen.

	// Coordinates in clip space
	vec4 clickClipSpace = vec4(clickPosition.x, clickPosition.y, -1, 1);

	// Eye-space coordinates are obtained by premultiplying by the inverse of the Projection matrix.
	vec4 viewModelp = inverse(this->projection->getProjectionMatrix()) * clickClipSpace;

	// World-space coordinates are obtained by premultiplying by the inverse of the View matrix.

	viewModelp.w = 1;
	vec4 Pw = inverse(this->camera->getViewMatrix()) * viewModelp;

	// The ray vector is computed by subtracting the camera position from the world-space point Pw.
	return normalize(vec3(Pw) - this->camera->getPosition());
}

tuple<PhysicalObject*, string> Scene::mousePicked(vec2 clickPosition) {
	vec3 direction = this->getRayFromMouseClick(clickPosition);
	float minDist = std::numeric_limits<float>::max();
	PhysicalObject* _selectedObj = nullptr;
	string _selectedMesh = "";
	for (PhysicalObject* o : this->objects) {
		tuple<string, float> mesh = o->selectNearestMesh(this->camera->getPosition(), direction);
		if (get<0>(mesh) != "" && get<1>(mesh) < minDist) {
			_selectedObj = o;
			_selectedMesh = get<0>(mesh);
			minDist = get<1>(mesh);
		}
	}
	return make_tuple(_selectedObj, _selectedMesh);
}

PhysicalObject* Scene::getSelectedObject() {
	return this->selectedObject;
}

tuple<string, Mesh*> Scene::getSelectedMesh() {
	if (this->selectedMesh == "") return { "", nullptr };
	
	return {this->selectedMesh, this->selectedObject->getMeshes()->at(this->selectedMesh)};
}

bool Scene::setSelectedObject(PhysicalObject* object) {
	auto iterator = std::find(this->objects.begin(), this->objects.end(), object);

	if (iterator != this->objects.end()) {
		this->selectedObject = object;
		return true;
	} else {
		this->resetObjectSelection();
		return false;
	}
}

bool Scene::setSelectedMesh(PhysicalObject* object, string mesh) {

	if (this->setSelectedObject(object)) {
		map<string, Mesh*>* meshes = this->selectedObject->getMeshes();

		auto it = meshes->find(mesh);

		if (it != meshes->end()) {
			this->selectedMesh = mesh;
			return true;
		} else {
			this->resetObjectSelection();
			return false;
		}

	} else {
		this->resetObjectSelection();
		return false;
	}
}

void Scene::resetMeshSelection() {
	this->selectedMesh = "";
}

void Scene::resetObjectSelection() {
	this->selectedMesh = "";
	this->selectedObject = nullptr;
}

PhysicalObject* Scene::loadObjectFromFile(const char* path) {
	PhysicalObject* loaded = this->objectFactory->createFromFile(path);
	if (loaded != nullptr) this->objects.push_back(loaded);
	return loaded;
}

void Scene::createLight() {
	if (this->lights.size() < MAX_LIGHTS) this->lights.push_back(new PointLight(this->lightShader));
}

void Scene::removeLight(int i) {
	if (i < this->lights.size()) {
		lights.erase(lights.begin() + i);
	}
}
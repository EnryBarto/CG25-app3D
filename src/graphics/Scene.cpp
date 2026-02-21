#include "Scene.h"
#include <limits>
#include <algorithm>

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
	for (PhysicalObject* o : this->objects) {
		o->render(v, p, c, anchor);
	}
}

vec3 Scene::getRayFromMouseClick(vec2 clickPosition) {
	clickPosition.y = this->windowManager->getCurrentResolution().y - clickPosition.y;

	// Map viewport coordinates [0,width], [0,height] in NDC [-1,1]  
	clickPosition = 2.0f * clickPosition / this->windowManager->getCurrentResolution() - 1.0f;

	//Nello spazio di clippling z più piccola, oggetto più vicino all'osservatore, quindi si pone la z a - 1, 
	// posizionando il punto sul piano vicino del frustum.
	// Questo significa che il raggio che stiamo calcolando partirà dalla telecamera e si dirigerà 
	// verso il punto più vicino visibile sullo schermo.
	
	// Coordinate nel clip space 
	vec4 clickClipSpace = vec4(clickPosition.x, clickPosition.y, -1, 1);

	// Le coordinate nell' eye space si ottengono premoltiplicando per l'inversa della matrice Projection.
	vec4 viewModelp = inverse(this->projection->getProjectionMatrix()) * clickClipSpace;

	// le coordinate nel world space: si ottengono premoltiplicando per l'inversa della matrice di Vista 

	viewModelp.w = 1;
	vec4 Pw = inverse(this->camera->getViewMatrix()) * viewModelp;

	//Il vettore del raggio viene calcolato sottraendo la posizione della telecamera SetupTelecamera.position dal punto Pw nel world space.
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
#pragma once

#define GLFW_INCLUDE_NONE

#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Projection.h"
#include "../utils/AppState.h"
#include "../utils/AppSettings.h"
#include "../utils/WindowManager.h"
#include "../shader/Shader.h"
#include "../lighting/Material.h"
#include "../lighting/PointLight.h"
#include "../entities/Mesh.h"
#include "../entities/Skybox.h"
#include "../entities/PhysicalObject.h"
#include "../geometry/MeshGeometry.h"

using namespace glm;
using namespace std;

class App; // Avoid recursive declaration
class PhysicalObjectFactory;

class Scene {

	friend class App; // The app must be able to access protected methods

	public:
		Scene(WindowManager* windowManager, AppSettings* currentSettings, Shader* defaultShader, Shader* basicShader, Material* defaultMaterial, Shader* skyboxShader, string skyboxCubemapDirectory);
		~Scene();
		Camera* getCamera();
		void update(float deltaTime, AppState currentState);
		void render();
		vector<PointLight*>* getLights();
		void createLight();
		void removeLight(int i);
		vector<PhysicalObject*>* getObjects();
		void removeObject(PhysicalObject* o);
		void addObject(PhysicalObject* toAdd);
		bool isCameraColliding();
		PhysicalObjectFactory* getObjectsFactory();

		// Object and mesh selection
		tuple<PhysicalObject*, string> mousePicked(vec2 clickPosition);
		PhysicalObject* getSelectedObject();
		tuple<string, Mesh*> getSelectedMesh();

	// The selection must be handled only by the App
	protected:
		bool setSelectedObject(PhysicalObject* object);
		bool setSelectedMesh(PhysicalObject* object, string mesh);
		void resetMeshSelection();
		void resetObjectSelection();
		PhysicalObject* loadObjectFromFile(const char* path);

	private:
		Camera* camera;
		Projection* projection;
		Skybox* skybox;
		Shader* basicShader; // Used to render bounding boxes and point lights
		vector<PhysicalObject*> objects;
		PhysicalObjectFactory* objectFactory;
		WindowManager* windowManager;
		GLFWwindow* window;
		AppSettings* currentSettings;
		vector<PointLight*> lights;
		
		vec3 getRayFromMouseClick(vec2 clickPosition);
		PhysicalObject* selectedObject = nullptr;
		string selectedMesh = "";
};
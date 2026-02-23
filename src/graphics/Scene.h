#pragma once

#include "../libs.h"
#include "Projection.h"
#include "Camera.h"
#include "renderable/Skybox.h"
#include "renderable/PhysicalObject.h"
#include "renderable/PhysicalObjectFactory.h"
#include "../graphics/WindowManager.h"
#include "../app/AppSettings.h"
#include "../app/AppState.h"
#include <tuple>
#include "lighting/Material.h"
#include "shader/Shader.h"
#include "lighting/PointLight.h"
#include <vector>

class App; // Avoid recursive declaration

class Scene {

	friend class App; // The app must be able to access protected methods

	public:
		Scene(WindowManager* windowManager, AppSettings* currentSettings, Shader* defaultShader, Shader*lightShader, Material* defaultMaterial, Shader* skyboxShader, string skyboxCubemapDirectory);
		~Scene();
		Camera* getCamera();
		void update(float deltaTime, AppState currentState);
		void render();
		vector<PointLight*>* getLights();
		void createLight();
		void removeLight(int i);

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
		Shader* lightShader;
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
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

class Scene {
	public:
		Scene(WindowManager* windowManager, AppSettings* currentSettings, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory);
		~Scene();
		Camera* getCamera();
		void update(float deltaTime, AppState currentState);
		void render();

	private:
		Camera* camera;
		Projection* projection;
		Skybox* skybox;
		vector<PhysicalObject*> objects;
		PhysicalObjectFactory* objectFactory;
		WindowManager* windowManager;
		GLFWwindow* window;
		AppSettings* currentSettings;
};
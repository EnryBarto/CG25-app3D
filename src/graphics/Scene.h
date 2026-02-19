#pragma once

#include "../libs.h"
#include "Projection.h"
#include "Camera.h"
#include "renderable/Skybox.h"
#include "renderable/PhysicalObject.h"
#include "renderable/PhysicalObjectFactory.h"
#include "../graphics/WindowManager.h"

class Scene {
	public:
		Scene(WindowManager* windowManager, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory);
		Camera* getCamera();
		void update(float deltaTime);
		void render();

	private:
		Camera* camera;
		Projection* projection;
		Skybox* skybox;
		vector<PhysicalObject*> objects;
		PhysicalObjectFactory* objectFactory;
		WindowManager* windowManager;
		GLFWwindow* window;
};
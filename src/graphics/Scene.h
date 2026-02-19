#pragma once

#include "../libs.h"
#include "Projection.h"
#include "Camera.h"
#include "renderable/Skybox.h"
#include "renderable/PhysicalObject.h"
#include "renderable/PhysicalObjectFactory.h"
#include "../app/MessageBus.h"

class Scene {
	public:
		Scene(int screenWidth, int screenHeight, Shader* defaultShader, Shader* skyboxShader, string skyboxCubemapDirectory);
		void update(float deltaTime);
		void render();
		MessageBus* getMessageBus();

	private:
		Camera* camera;
		Projection* projection;
		Skybox* skybox;
		vector<PhysicalObject*> objects;
		PhysicalObjectFactory* objectFactory;
		MessageBus messageBus;
};
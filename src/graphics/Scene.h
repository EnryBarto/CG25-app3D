#pragma once

#include "../libs.h"
#include "Projection.h"
#include "Camera.h"
#include "renderable/Skybox.h"

class Scene {
	public:
		Scene(int screenWidth, int screenHeight, Shader* skyboxShader, string skyboxCubemapDirectory);
		void render();

	private:
		Camera* camera;
		Projection* projection;
		Skybox* skybox;
};
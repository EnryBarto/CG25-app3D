#pragma once

#include "Projection.h"
#include "Camera.h"

class Scene {
	public:
		Scene(int screenWidth, int screenHeight);
		void render();

	private:
		Camera* camera;
		Projection* projection;
};
#pragma once

#include <map>
#include "../graphics/shader/Shader.h"
#include "../graphics/Scene.h"
#include "../graphics/WindowManager.h"
#include "AppSettings.h"
#include "AppState.h"
#include "../graphics/Camera.h"
#include <string>

class App {
	public:
		App();
		~App();
		void update(float deltaTime);
		void render();
		void close();
		AppState getCurrentAppState();
		void togglePause();
		void toggleMode();
		WindowManager* getWindowManager();
		Scene* getScene();
		AppSettings* getAppSettings();

	private:
		map<string, Shader*>* shaders;
		AppState currentState;
		AppState precState;
		AppSettings* currentSettings;
		WindowManager* windowManager;
		Scene* scene;
};
#pragma once

#include <map>
#include "../graphics/shader/Shader.h"
#include "../graphics/Scene.h"
#include "../graphics/WindowManager.h"
#include "AppSettings.h"
#include "AppState.h"
#include "../graphics/Camera.h"
#include <string>
#include <stack>
#include <queue>

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
		void escPressed();
		map<string, Shader*>* getShaders();

		// Object and mesh selection
		void pick(vec2 clickPosition);
		void setSelectedObject(PhysicalObject* selected);
		void setSelectedMesh(PhysicalObject* selectedObject, string selectedMesh);
		void resetObjectSelection();
		void resetMeshSelection();

		// File upload
		void loadObjectsFromFile(const char* paths[], int numFiles);
		void confirmFileUploadError();
		void confirmFileUploadSuccess();

	private:
		map<string, Shader*>* shaders;
		AppSettings* currentSettings;
		WindowManager* windowManager;
		Scene* scene;
		AppState nextState;
		AppState currentState;
		stack<AppState> statesHistory;
		queue<string> filesToLoad;
		char stringBuffer[100];
		void setNextStateFromHistory();
		void loopFileUpload();
};
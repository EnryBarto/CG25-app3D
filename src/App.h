#pragma once

#include <map>
#include <queue>
#include <stack>
#include <string>
#include <glm/glm.hpp>

#include "utils/AppState.h"
#include "utils/AppSettings.h"
#include "utils/WindowManager.h"
#include "scene/Scene.h"
#include "shader/Shader.h"
#include "lighting/Material.h"
#include "texture/Texture.h"
#include "entities/PhysicalObject.h"

using namespace std;
using namespace glm;

class App {
	public:
		App();
		~App();
		void update(float deltaTime);
		void render();
		void close();
		AppState getCurrentAppState();
		void togglePause();
		void toggleObjectList();
		void toggleMode();
		void toggleMovingTrackball();
		WindowManager* getWindowManager();
		Scene* getScene();
		AppSettings* getAppSettings();
		void escPressed();
		map<string, Shader*>* getShaders();
		map<string, Material*>* getMaterials();
		map<string, Texture*>* getTextures();
		void toggleLightSettings();

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
		map<string, Material*>* materials;
		map<string, Texture*>* textures;
		Shader* cubemapShader;
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
		static bool compareStrings(string str1, string str2);
};